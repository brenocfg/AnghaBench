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
struct TYPE_2__ {int /*<<< orphan*/  (* irq_ack ) (struct fmc_device*) ;} ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/  (*) (struct fmc_device*)) ; 
 int /*<<< orphan*/  stub1 (struct fmc_device*) ; 

void fmc_irq_ack(struct fmc_device *fmc)
{
	if (likely(fmc->op->irq_ack))
		fmc->op->irq_ack(fmc);
}