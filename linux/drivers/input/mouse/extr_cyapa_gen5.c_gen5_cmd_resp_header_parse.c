#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct cyapa_pip_cmd_states {scalar_t__* empty_buf; } ;
struct TYPE_2__ {struct cyapa_pip_cmd_states pip; } ;
struct cyapa {void* state; void* gen; TYPE_1__ cmd_states; } ;

/* Variables and functions */
 void* CYAPA_GEN5 ; 
 void* CYAPA_STATE_GEN5_APP ; 
 void* CYAPA_STATE_GEN5_BL ; 
 void* CYAPA_STATE_NO_DEVICE ; 
 int EIO ; 
 scalar_t__ PIP_APP_RESP_REPORT_ID ; 
 scalar_t__ PIP_BL_RESP_REPORT_ID ; 
 scalar_t__ PIP_EOP_KEY ; 
 size_t PIP_RESP_BL_SOP_OFFSET ; 
 size_t PIP_RESP_LENGTH_OFFSET ; 
 int PIP_RESP_LENGTH_SIZE ; 
 size_t PIP_RESP_REPORT_ID_OFFSET ; 
 scalar_t__ PIP_RESP_RSVD_KEY ; 
 size_t PIP_RESP_RSVD_OFFSET ; 
 scalar_t__ PIP_SOP_KEY ; 
 int cyapa_i2c_pip_read (struct cyapa*,scalar_t__*,int) ; 
 int get_unaligned_le16 (scalar_t__*) ; 

__attribute__((used)) static int gen5_cmd_resp_header_parse(struct cyapa *cyapa, u8 *reg_data)
{
	struct cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	int length;
	int ret;

	/*
	 * Must read report data through out,
	 * otherwise Gen5 trackpad cannot response next command
	 * or report any touch or button data.
	 */
	length = get_unaligned_le16(&reg_data[PIP_RESP_LENGTH_OFFSET]);
	ret = cyapa_i2c_pip_read(cyapa, pip->empty_buf, length);
	if (ret != length)
		return ret < 0 ? ret : -EIO;

	if (length == PIP_RESP_LENGTH_SIZE) {
		/* Previous command has read the data through out. */
		if (reg_data[PIP_RESP_REPORT_ID_OFFSET] ==
				PIP_BL_RESP_REPORT_ID) {
			/* Gen5 BL command response data detected */
			cyapa->gen = CYAPA_GEN5;
			cyapa->state = CYAPA_STATE_GEN5_BL;
		} else {
			/* Gen5 APP command response data detected */
			cyapa->gen = CYAPA_GEN5;
			cyapa->state = CYAPA_STATE_GEN5_APP;
		}
	} else if ((pip->empty_buf[PIP_RESP_REPORT_ID_OFFSET] ==
				PIP_BL_RESP_REPORT_ID) &&
			(pip->empty_buf[PIP_RESP_RSVD_OFFSET] ==
				PIP_RESP_RSVD_KEY) &&
			(pip->empty_buf[PIP_RESP_BL_SOP_OFFSET] ==
				PIP_SOP_KEY) &&
			(pip->empty_buf[length - 1] ==
				PIP_EOP_KEY)) {
		/* Gen5 BL command response data detected */
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = CYAPA_STATE_GEN5_BL;
	} else if (pip->empty_buf[PIP_RESP_REPORT_ID_OFFSET] ==
				PIP_APP_RESP_REPORT_ID &&
			pip->empty_buf[PIP_RESP_RSVD_OFFSET] ==
				PIP_RESP_RSVD_KEY) {
		/* Gen5 APP command response data detected */
		cyapa->gen = CYAPA_GEN5;
		cyapa->state = CYAPA_STATE_GEN5_APP;
	} else {
		/* Should not happen!!! */
		cyapa->state = CYAPA_STATE_NO_DEVICE;
	}

	return 0;
}