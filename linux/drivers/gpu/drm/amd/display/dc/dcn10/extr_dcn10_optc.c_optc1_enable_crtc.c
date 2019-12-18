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
struct timing_generator {int inst; } ;
struct optc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL ; 
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OPTC_DATA_SOURCE_SELECT ; 
 int /*<<< orphan*/  OPTC_SRC_SEL ; 
 int /*<<< orphan*/  OTG_CONTROL ; 
 int /*<<< orphan*/  OTG_DISABLE_POINT_CNTL ; 
 int /*<<< orphan*/  OTG_MASTER_EN ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VTG0_ENABLE ; 

__attribute__((used)) static bool optc1_enable_crtc(struct timing_generator *optc)
{
	/* TODO FPGA wait for answer
	 * OTG_MASTER_UPDATE_MODE != CRTC_MASTER_UPDATE_MODE
	 * OTG_MASTER_UPDATE_LOCK != CRTC_MASTER_UPDATE_LOCK
	 */
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	/* opp instance for OTG. For DCN1.0, ODM is remoed.
	 * OPP and OPTC should 1:1 mapping
	 */
	REG_UPDATE(OPTC_DATA_SOURCE_SELECT,
			OPTC_SRC_SEL, optc->inst);

	/* VTG enable first is for HW workaround */
	REG_UPDATE(CONTROL,
			VTG0_ENABLE, 1);

	/* Enable CRTC */
	REG_UPDATE_2(OTG_CONTROL,
			OTG_DISABLE_POINT_CNTL, 3,
			OTG_MASTER_EN, 1);

	return true;
}