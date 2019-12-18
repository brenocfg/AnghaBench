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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct dce_aux {int dummy; } ;
struct aux_engine_dce110 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_SW_AUTOINCREMENT_DISABLE ; 
 int /*<<< orphan*/  AUX_SW_DATA ; 
 int /*<<< orphan*/  AUX_SW_DATA_RW ; 
 int /*<<< orphan*/  AUX_SW_INDEX ; 
 int /*<<< orphan*/  AUX_SW_REPLY_BYTE_COUNT ; 
 int /*<<< orphan*/  AUX_SW_STATUS ; 
 int AUX_SW_STATUS__AUX_SW_HPD_DISCON_MASK ; 
 struct aux_engine_dce110* FROM_AUX_ENGINE (struct dce_aux*) ; 
 int REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  REG_UPDATE_SEQ_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int read_channel_reply(struct dce_aux *engine, uint32_t size,
			      uint8_t *buffer, uint8_t *reply_result,
			      uint32_t *sw_status)
{
	struct aux_engine_dce110 *aux110 = FROM_AUX_ENGINE(engine);
	uint32_t bytes_replied;
	uint32_t reply_result_32;

	*sw_status = REG_GET(AUX_SW_STATUS, AUX_SW_REPLY_BYTE_COUNT,
			     &bytes_replied);

	/* In case HPD is LOW, exit AUX transaction */
	if ((*sw_status & AUX_SW_STATUS__AUX_SW_HPD_DISCON_MASK))
		return -1;

	/* Need at least the status byte */
	if (!bytes_replied)
		return -1;

	REG_UPDATE_SEQ_3(AUX_SW_DATA,
			  AUX_SW_INDEX, 0,
			  AUX_SW_AUTOINCREMENT_DISABLE, 1,
			  AUX_SW_DATA_RW, 1);

	REG_GET(AUX_SW_DATA, AUX_SW_DATA, &reply_result_32);
	reply_result_32 = reply_result_32 >> 4;
	if (reply_result != NULL)
		*reply_result = (uint8_t)reply_result_32;

	if (reply_result_32 == 0) { /* ACK */
		uint32_t i = 0;

		/* First byte was already used to get the command status */
		--bytes_replied;

		/* Do not overflow buffer */
		if (bytes_replied > size)
			return -1;

		while (i < bytes_replied) {
			uint32_t aux_sw_data_val;

			REG_GET(AUX_SW_DATA, AUX_SW_DATA, &aux_sw_data_val);
			buffer[i] = aux_sw_data_val;
			++i;
		}

		return i;
	}

	return 0;
}