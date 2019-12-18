#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct cyapa {int /*<<< orphan*/  state; int /*<<< orphan*/  gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  CYAPA_GEN5 ; 
 int /*<<< orphan*/  CYAPA_STATE_GEN5_APP ; 
 int EINVAL ; 
#define  GEN5_OLD_PUSH_BTN_REPORT_ID 132 
 int PIP_BTN_REPORT_HEAD_SIZE ; 
#define  PIP_BTN_REPORT_ID 131 
 int PIP_BTN_REPORT_MAX_SIZE ; 
#define  PIP_PUSH_BTN_REPORT_ID 130 
 size_t PIP_RESP_LENGTH_OFFSET ; 
 size_t PIP_RESP_REPORT_ID_OFFSET ; 
 int PIP_TOUCH_REPORT_HEAD_SIZE ; 
#define  PIP_TOUCH_REPORT_ID 129 
 int PIP_TOUCH_REPORT_MAX_SIZE ; 
#define  PIP_WAKEUP_EVENT_REPORT_ID 128 
 int PIP_WAKEUP_EVENT_SIZE ; 
 int get_unaligned_le16 (int*) ; 

__attribute__((used)) static int gen5_report_data_header_parse(struct cyapa *cyapa, u8 *reg_data)
{
	int length;

	length = get_unaligned_le16(&reg_data[PIP_RESP_LENGTH_OFFSET]);
	switch (reg_data[PIP_RESP_REPORT_ID_OFFSET]) {
	case PIP_TOUCH_REPORT_ID:
		if (length < PIP_TOUCH_REPORT_HEAD_SIZE ||
			length > PIP_TOUCH_REPORT_MAX_SIZE)
			return -EINVAL;
		break;
	case PIP_BTN_REPORT_ID:
	case GEN5_OLD_PUSH_BTN_REPORT_ID:
	case PIP_PUSH_BTN_REPORT_ID:
		if (length < PIP_BTN_REPORT_HEAD_SIZE ||
			length > PIP_BTN_REPORT_MAX_SIZE)
			return -EINVAL;
		break;
	case PIP_WAKEUP_EVENT_REPORT_ID:
		if (length != PIP_WAKEUP_EVENT_SIZE)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	cyapa->gen = CYAPA_GEN5;
	cyapa->state = CYAPA_STATE_GEN5_APP;
	return 0;
}