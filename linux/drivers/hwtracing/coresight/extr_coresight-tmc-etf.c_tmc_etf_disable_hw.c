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
struct tmc_drvdata {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coresight_disclaim_device_unlocked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmc_disable_hw (struct tmc_drvdata*) ; 
 int /*<<< orphan*/  tmc_flush_and_stop (struct tmc_drvdata*) ; 

__attribute__((used)) static void tmc_etf_disable_hw(struct tmc_drvdata *drvdata)
{
	CS_UNLOCK(drvdata->base);

	tmc_flush_and_stop(drvdata);
	tmc_disable_hw(drvdata);
	coresight_disclaim_device_unlocked(drvdata->base);
	CS_LOCK(drvdata->base);
}