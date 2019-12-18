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
struct hubp {int dummy; } ;
struct dcn20_hubp {int dummy; } ;
struct TYPE_2__ {int high_part; int /*<<< orphan*/  low_part; } ;
struct dc_dmdata_attributes {scalar_t__ dmdata_mode; int /*<<< orphan*/  dmdata_dl_delta; int /*<<< orphan*/  dmdata_qos_level; int /*<<< orphan*/  dmdata_qos_mode; int /*<<< orphan*/  dmdata_sw_data; int /*<<< orphan*/  dmdata_size; int /*<<< orphan*/  dmdata_repeat; TYPE_1__ address; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCSURF_FLIP_CONTROL ; 
 int /*<<< orphan*/  DMDATA_ADDRESS_HIGH ; 
 int /*<<< orphan*/  DMDATA_ADDRESS_LOW ; 
 int /*<<< orphan*/  DMDATA_CNTL ; 
 int /*<<< orphan*/  DMDATA_DL_DELTA ; 
 scalar_t__ DMDATA_HW_MODE ; 
 int /*<<< orphan*/  DMDATA_MODE ; 
 int /*<<< orphan*/  DMDATA_QOS_CNTL ; 
 int /*<<< orphan*/  DMDATA_QOS_LEVEL ; 
 int /*<<< orphan*/  DMDATA_QOS_MODE ; 
 int /*<<< orphan*/  DMDATA_REPEAT ; 
 int /*<<< orphan*/  DMDATA_SIZE ; 
 int /*<<< orphan*/  DMDATA_SW_CNTL ; 
 int /*<<< orphan*/  DMDATA_SW_REPEAT ; 
 int /*<<< orphan*/  DMDATA_SW_SIZE ; 
 int /*<<< orphan*/  DMDATA_SW_UPDATED ; 
 int /*<<< orphan*/  DMDATA_UPDATED ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SURFACE_UPDATE_LOCK ; 
 struct dcn20_hubp* TO_DCN20_HUBP (struct hubp*) ; 
 int /*<<< orphan*/  hubp2_dmdata_load (struct hubp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hubp2_dmdata_set_attributes(
		struct hubp *hubp,
		const struct dc_dmdata_attributes *attr)
{
	struct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	if (attr->dmdata_mode == DMDATA_HW_MODE) {
		/* set to HW mode */
		REG_UPDATE(DMDATA_CNTL,
				DMDATA_MODE, 1);

		/* for DMDATA flip, need to use SURFACE_UPDATE_LOCK */
		REG_UPDATE(DCSURF_FLIP_CONTROL, SURFACE_UPDATE_LOCK, 1);

		/* toggle DMDATA_UPDATED and set repeat and size */
		REG_UPDATE(DMDATA_CNTL,
				DMDATA_UPDATED, 0);
		REG_UPDATE_3(DMDATA_CNTL,
				DMDATA_UPDATED, 1,
				DMDATA_REPEAT, attr->dmdata_repeat,
				DMDATA_SIZE, attr->dmdata_size);

		/* set DMDATA address */
		REG_WRITE(DMDATA_ADDRESS_LOW, attr->address.low_part);
		REG_UPDATE(DMDATA_ADDRESS_HIGH,
				DMDATA_ADDRESS_HIGH, attr->address.high_part);

		REG_UPDATE(DCSURF_FLIP_CONTROL, SURFACE_UPDATE_LOCK, 0);

	} else {
		/* set to SW mode before loading data */
		REG_SET(DMDATA_CNTL, 0,
				DMDATA_MODE, 0);
		/* toggle DMDATA_SW_UPDATED to start loading sequence */
		REG_UPDATE(DMDATA_SW_CNTL,
				DMDATA_SW_UPDATED, 0);
		REG_UPDATE_3(DMDATA_SW_CNTL,
				DMDATA_SW_UPDATED, 1,
				DMDATA_SW_REPEAT, attr->dmdata_repeat,
				DMDATA_SW_SIZE, attr->dmdata_size);
		/* load data into hubp dmdata buffer */
		hubp2_dmdata_load(hubp, attr->dmdata_size, attr->dmdata_sw_data);
	}

	/* Note that DL_DELTA must be programmed if we want to use TTU mode */
	REG_SET_3(DMDATA_QOS_CNTL, 0,
			DMDATA_QOS_MODE, attr->dmdata_qos_mode,
			DMDATA_QOS_LEVEL, attr->dmdata_qos_level,
			DMDATA_DL_DELTA, attr->dmdata_dl_delta);
}