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
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_FORCE_COUNT_NOW_CLEAR ; 
 int /*<<< orphan*/  OTG_FORCE_COUNT_NOW_CNTL ; 
 int /*<<< orphan*/  OTG_FORCE_VSYNC_NEXT_LINE_CLEAR ; 
 int /*<<< orphan*/  OTG_TRIGA_CNTL ; 
 int /*<<< orphan*/  OTG_VERT_SYNC_CONTROL ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void optc1_disable_reset_trigger(struct timing_generator *optc)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_WRITE(OTG_TRIGA_CNTL, 0);

	REG_SET(OTG_FORCE_COUNT_NOW_CNTL, 0,
		OTG_FORCE_COUNT_NOW_CLEAR, 1);

	REG_SET(OTG_VERT_SYNC_CONTROL, 0,
		OTG_FORCE_VSYNC_NEXT_LINE_CLEAR, 1);
}