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
struct fimc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fimc_hw_disable_capture (struct fimc_dev*) ; 
 int /*<<< orphan*/  fimc_hw_en_lastirq (struct fimc_dev*,int) ; 
 int /*<<< orphan*/  fimc_hw_enable_scaler (struct fimc_dev*,int) ; 

void fimc_deactivate_capture(struct fimc_dev *fimc)
{
	fimc_hw_en_lastirq(fimc, true);
	fimc_hw_disable_capture(fimc);
	fimc_hw_enable_scaler(fimc, false);
	fimc_hw_en_lastirq(fimc, false);
}