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
struct stm_drvdata {int stmspscr; int stmsper; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  CS_UNLOCK (scalar_t__) ; 
 scalar_t__ STMSPER ; 
 scalar_t__ STMSPSCR ; 
 scalar_t__ STMSPTRIGCSR ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void stm_port_enable_hw(struct stm_drvdata *drvdata)
{
	CS_UNLOCK(drvdata->base);
	/* ATB trigger enable on direct writes to TRIG locations */
	writel_relaxed(0x10,
		       drvdata->base + STMSPTRIGCSR);
	writel_relaxed(drvdata->stmspscr, drvdata->base + STMSPSCR);
	writel_relaxed(drvdata->stmsper, drvdata->base + STMSPER);

	CS_LOCK(drvdata->base);
}