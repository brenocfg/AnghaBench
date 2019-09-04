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
struct timing_generator {int dummy; } ;
struct optc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL ; 
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_BUSY ; 
 int /*<<< orphan*/  OTG_CLOCK_CONTROL ; 
 int /*<<< orphan*/  OTG_CONTROL ; 
 int /*<<< orphan*/  OTG_DISABLE_POINT_CNTL ; 
 int /*<<< orphan*/  OTG_MASTER_EN ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  VTG0_ENABLE ; 

bool optc1_disable_crtc(struct timing_generator *optc)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	/* disable otg request until end of the first line
	 * in the vertical blank region
	 */
	REG_UPDATE_2(OTG_CONTROL,
			OTG_DISABLE_POINT_CNTL, 3,
			OTG_MASTER_EN, 0);

	REG_UPDATE(CONTROL,
			VTG0_ENABLE, 0);

	/* CRTC disabled, so disable  clock. */
	REG_WAIT(OTG_CLOCK_CONTROL,
			OTG_BUSY, 0,
			1, 100000);

	return true;
}