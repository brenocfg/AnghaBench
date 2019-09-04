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
struct timing_generator {int dummy; } ;
struct optc {int dummy; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_FORCE_COUNT_NOW_CNTL ; 
 int /*<<< orphan*/  OTG_FORCE_COUNT_NOW_OCCURRED ; 
 int /*<<< orphan*/  OTG_FORCE_VSYNC_NEXT_LINE_OCCURRED ; 
 int /*<<< orphan*/  OTG_VERT_SYNC_CONTROL ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

bool optc1_did_triggered_reset_occur(
	struct timing_generator *optc)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);
	uint32_t occurred_force, occurred_vsync;

	REG_GET(OTG_FORCE_COUNT_NOW_CNTL,
		OTG_FORCE_COUNT_NOW_OCCURRED, &occurred_force);

	REG_GET(OTG_VERT_SYNC_CONTROL,
		OTG_FORCE_VSYNC_NEXT_LINE_OCCURRED, &occurred_vsync);

	return occurred_vsync != 0 || occurred_force != 0;
}