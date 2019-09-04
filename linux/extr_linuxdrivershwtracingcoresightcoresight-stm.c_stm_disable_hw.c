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
typedef  int u32 ;
struct stm_drvdata {scalar_t__ stmheer; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  CS_UNLOCK (scalar_t__) ; 
 scalar_t__ STMTCSR ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  stm_hwevent_disable_hw (struct stm_drvdata*) ; 
 int /*<<< orphan*/  stm_port_disable_hw (struct stm_drvdata*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void stm_disable_hw(struct stm_drvdata *drvdata)
{
	u32 val;

	CS_UNLOCK(drvdata->base);

	val = readl_relaxed(drvdata->base + STMTCSR);
	val &= ~0x1; /* clear global STM enable [0] */
	writel_relaxed(val, drvdata->base + STMTCSR);

	CS_LOCK(drvdata->base);

	stm_port_disable_hw(drvdata);
	if (drvdata->stmheer)
		stm_hwevent_disable_hw(drvdata);
}