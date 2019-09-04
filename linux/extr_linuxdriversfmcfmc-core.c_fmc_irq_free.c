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
struct fmc_device {TYPE_1__* op; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* irq_free ) (struct fmc_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct fmc_device*) ; 

void fmc_irq_free(struct fmc_device *fmc)
{
	if (fmc->op->irq_free)
		fmc->op->irq_free(fmc);
}