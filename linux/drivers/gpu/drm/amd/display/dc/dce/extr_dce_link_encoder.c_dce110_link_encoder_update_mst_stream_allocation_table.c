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
typedef  scalar_t__ uint32_t ;
struct link_mst_stream_allocation_table {int stream_count; int /*<<< orphan*/ * stream_allocations; } ;
struct link_encoder {int dummy; } ;
struct dce110_link_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_MSE_16_MTP_KEEPOUT ; 
 int /*<<< orphan*/  DP_MSE_SAT0 ; 
 int /*<<< orphan*/  DP_MSE_SAT1 ; 
 int /*<<< orphan*/  DP_MSE_SAT_SLOT_COUNT0 ; 
 int /*<<< orphan*/  DP_MSE_SAT_SLOT_COUNT1 ; 
 int /*<<< orphan*/  DP_MSE_SAT_SLOT_COUNT2 ; 
 int /*<<< orphan*/  DP_MSE_SAT_SLOT_COUNT3 ; 
 int /*<<< orphan*/  DP_MSE_SAT_SRC0 ; 
 int /*<<< orphan*/  DP_MSE_SAT_SRC1 ; 
 int /*<<< orphan*/  DP_MSE_SAT_SRC2 ; 
 int /*<<< orphan*/  DP_MSE_SAT_SRC3 ; 
 int /*<<< orphan*/  DP_MSE_SAT_UPDATE ; 
 scalar_t__ DP_MST_UPDATE_MAX_RETRY ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 struct dce110_link_encoder* TO_DCE110_LINK_ENC (struct link_encoder*) ; 
 int /*<<< orphan*/  fill_stream_allocation_row_info (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  udelay (int) ; 

void dce110_link_encoder_update_mst_stream_allocation_table(
	struct link_encoder *enc,
	const struct link_mst_stream_allocation_table *table)
{
	struct dce110_link_encoder *enc110 = TO_DCE110_LINK_ENC(enc);
	uint32_t value0 = 0;
	uint32_t value1 = 0;
	uint32_t value2 = 0;
	uint32_t slots = 0;
	uint32_t src = 0;
	uint32_t retries = 0;

	/* For CZ, there are only 3 pipes. So Virtual channel is up 3.*/

	/* --- Set MSE Stream Attribute -
	 * Setup VC Payload Table on Tx Side,
	 * Issue allocation change trigger
	 * to commit payload on both tx and rx side */

	/* we should clean-up table each time */

	if (table->stream_count >= 1) {
		fill_stream_allocation_row_info(
			&table->stream_allocations[0],
			&src,
			&slots);
	} else {
		src = 0;
		slots = 0;
	}

	REG_UPDATE_2(DP_MSE_SAT0,
			DP_MSE_SAT_SRC0, src,
			DP_MSE_SAT_SLOT_COUNT0, slots);

	if (table->stream_count >= 2) {
		fill_stream_allocation_row_info(
			&table->stream_allocations[1],
			&src,
			&slots);
	} else {
		src = 0;
		slots = 0;
	}

	REG_UPDATE_2(DP_MSE_SAT0,
			DP_MSE_SAT_SRC1, src,
			DP_MSE_SAT_SLOT_COUNT1, slots);

	if (table->stream_count >= 3) {
		fill_stream_allocation_row_info(
			&table->stream_allocations[2],
			&src,
			&slots);
	} else {
		src = 0;
		slots = 0;
	}

	REG_UPDATE_2(DP_MSE_SAT1,
			DP_MSE_SAT_SRC2, src,
			DP_MSE_SAT_SLOT_COUNT2, slots);

	if (table->stream_count >= 4) {
		fill_stream_allocation_row_info(
			&table->stream_allocations[3],
			&src,
			&slots);
	} else {
		src = 0;
		slots = 0;
	}

	REG_UPDATE_2(DP_MSE_SAT1,
			DP_MSE_SAT_SRC3, src,
			DP_MSE_SAT_SLOT_COUNT3, slots);

	/* --- wait for transaction finish */

	/* send allocation change trigger (ACT) ?
	 * this step first sends the ACT,
	 * then double buffers the SAT into the hardware
	 * making the new allocation active on the DP MST mode link */


	/* DP_MSE_SAT_UPDATE:
	 * 0 - No Action
	 * 1 - Update SAT with trigger
	 * 2 - Update SAT without trigger */

	REG_UPDATE(DP_MSE_SAT_UPDATE,
			DP_MSE_SAT_UPDATE, 1);

	/* wait for update to complete
	 * (i.e. DP_MSE_SAT_UPDATE field is reset to 0)
	 * then wait for the transmission
	 * of at least 16 MTP headers on immediate local link.
	 * i.e. DP_MSE_16_MTP_KEEPOUT field (read only) is reset to 0
	 * a value of 1 indicates that DP MST mode
	 * is in the 16 MTP keepout region after a VC has been added.
	 * MST stream bandwidth (VC rate) can be configured
	 * after this bit is cleared */

	do {
		udelay(10);

		value0 = REG_READ(DP_MSE_SAT_UPDATE);

		REG_GET(DP_MSE_SAT_UPDATE,
				DP_MSE_SAT_UPDATE, &value1);

		REG_GET(DP_MSE_SAT_UPDATE,
				DP_MSE_16_MTP_KEEPOUT, &value2);

		/* bit field DP_MSE_SAT_UPDATE is set to 1 already */
		if (!value1 && !value2)
			break;
		++retries;
	} while (retries < DP_MST_UPDATE_MAX_RETRY);
}