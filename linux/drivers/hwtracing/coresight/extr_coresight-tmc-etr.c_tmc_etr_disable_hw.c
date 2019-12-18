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
struct tmc_drvdata {int /*<<< orphan*/ * etr_buf; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tmc_etr_disable_hw (struct tmc_drvdata*) ; 
 int /*<<< orphan*/  coresight_disclaim_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmc_etr_disable_catu (struct tmc_drvdata*) ; 

__attribute__((used)) static void tmc_etr_disable_hw(struct tmc_drvdata *drvdata)
{
	__tmc_etr_disable_hw(drvdata);
	/* Disable CATU device if this ETR is connected to one */
	tmc_etr_disable_catu(drvdata);
	coresight_disclaim_device(drvdata->base);
	/* Reset the ETR buf used by hardware */
	drvdata->etr_buf = NULL;
}