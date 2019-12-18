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
typedef  int uint32_t ;
struct timing_generator {int inst; TYPE_1__* ctx; } ;
struct optc {int dummy; } ;
struct TYPE_2__ {scalar_t__ dce_environment; } ;

/* Variables and functions */
 scalar_t__ DCE_ENV_FPGA_MAXIMUS ; 
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_CONTROL ; 
 int /*<<< orphan*/  OTG_GLOBAL_CONTROL0 ; 
 int /*<<< orphan*/  OTG_MASTER_UPDATE_LOCK ; 
 int /*<<< orphan*/  OTG_MASTER_UPDATE_LOCK_SEL ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  UPDATE_LOCK_STATUS ; 

void optc1_lock(struct timing_generator *optc)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);
	uint32_t regval = 0;

	regval = REG_READ(OTG_CONTROL);

	/* otg is not running, do not need to be locked */
	if ((regval & 0x1) == 0x0)
		return;

	REG_SET(OTG_GLOBAL_CONTROL0, 0,
			OTG_MASTER_UPDATE_LOCK_SEL, optc->inst);
	REG_SET(OTG_MASTER_UPDATE_LOCK, 0,
			OTG_MASTER_UPDATE_LOCK, 1);

	/* Should be fast, status does not update on maximus */
	if (optc->ctx->dce_environment != DCE_ENV_FPGA_MAXIMUS) {

		REG_WAIT(OTG_MASTER_UPDATE_LOCK,
				UPDATE_LOCK_STATUS, 1,
				1, 10);
	}
}