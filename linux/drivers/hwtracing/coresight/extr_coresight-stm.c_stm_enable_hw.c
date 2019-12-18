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
struct stm_drvdata {int traceid; scalar_t__ base; scalar_t__ stmheer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  CS_UNLOCK (scalar_t__) ; 
 scalar_t__ STMSYNCR ; 
 scalar_t__ STMTCSR ; 
 int /*<<< orphan*/  stm_hwevent_enable_hw (struct stm_drvdata*) ; 
 int /*<<< orphan*/  stm_port_enable_hw (struct stm_drvdata*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void stm_enable_hw(struct stm_drvdata *drvdata)
{
	if (drvdata->stmheer)
		stm_hwevent_enable_hw(drvdata);

	stm_port_enable_hw(drvdata);

	CS_UNLOCK(drvdata->base);

	/* 4096 byte between synchronisation packets */
	writel_relaxed(0xFFF, drvdata->base + STMSYNCR);
	writel_relaxed((drvdata->traceid << 16 | /* trace id */
			0x02 |			 /* timestamp enable */
			0x01),			 /* global STM enable */
			drvdata->base + STMTCSR);

	CS_LOCK(drvdata->base);
}