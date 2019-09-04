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

/* Variables and functions */
 int /*<<< orphan*/  ISIF_SYNCEN_VDHDEN_MASK ; 
 int /*<<< orphan*/  SYNCEN ; 
 int /*<<< orphan*/  isif_disable_all_modules () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_modify (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isif_enable(int en)
{
	if (!en) {
		/* Before disable isif, disable all ISIF modules */
		isif_disable_all_modules();
		/*
		 * wait for next VD. Assume lowest scan rate is 12 Hz. So
		 * 100 msec delay is good enough
		 */
		msleep(100);
	}
	reg_modify(ISIF_SYNCEN_VDHDEN_MASK, en, SYNCEN);
}