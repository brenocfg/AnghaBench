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
struct etmv4_drvdata {int os_unlock; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ TRCOSLAR ; 
 int /*<<< orphan*/  isb () ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void etm4_os_unlock(struct etmv4_drvdata *drvdata)
{
	/* Writing 0 to TRCOSLAR unlocks the trace registers */
	writel_relaxed(0x0, drvdata->base + TRCOSLAR);
	drvdata->os_unlock = true;
	isb();
}