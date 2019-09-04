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
typedef  int /*<<< orphan*/  uint32_t ;
struct msm_gpu {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REG_A3XX_RBBM_INT_0_STATUS ; 
 int /*<<< orphan*/  REG_A3XX_RBBM_INT_CLEAR_CMD ; 
 int /*<<< orphan*/  gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_gpu_retire (struct msm_gpu*) ; 

__attribute__((used)) static irqreturn_t a3xx_irq(struct msm_gpu *gpu)
{
	uint32_t status;

	status = gpu_read(gpu, REG_A3XX_RBBM_INT_0_STATUS);
	DBG("%s: %08x", gpu->name, status);

	// TODO

	gpu_write(gpu, REG_A3XX_RBBM_INT_CLEAR_CMD, status);

	msm_gpu_retire(gpu);

	return IRQ_HANDLED;
}