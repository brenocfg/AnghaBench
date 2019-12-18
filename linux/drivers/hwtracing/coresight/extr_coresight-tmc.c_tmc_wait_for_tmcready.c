#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tmc_drvdata {TYPE_1__* csdev; int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TMC_STS ; 
 int /*<<< orphan*/  TMC_STS_TMCREADY_BIT ; 
 scalar_t__ coresight_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

void tmc_wait_for_tmcready(struct tmc_drvdata *drvdata)
{
	/* Ensure formatter, unformatter and hardware fifo are empty */
	if (coresight_timeout(drvdata->base,
			      TMC_STS, TMC_STS_TMCREADY_BIT, 1)) {
		dev_err(&drvdata->csdev->dev,
			"timeout while waiting for TMC to be Ready\n");
	}
}