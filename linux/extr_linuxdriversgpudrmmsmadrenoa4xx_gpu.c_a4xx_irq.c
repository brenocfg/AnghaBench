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
typedef  int uint32_t ;
struct msm_gpu {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int A4XX_INT0_CP_REG_PROTECT_FAULT ; 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REG_A4XX_CP_PROTECT_STATUS ; 
 int /*<<< orphan*/  REG_A4XX_RBBM_INT_0_STATUS ; 
 int /*<<< orphan*/  REG_A4XX_RBBM_INT_CLEAR_CMD ; 
 int gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msm_gpu_retire (struct msm_gpu*) ; 
 int /*<<< orphan*/  printk (char*,char*,int) ; 

__attribute__((used)) static irqreturn_t a4xx_irq(struct msm_gpu *gpu)
{
	uint32_t status;

	status = gpu_read(gpu, REG_A4XX_RBBM_INT_0_STATUS);
	DBG("%s: Int status %08x", gpu->name, status);

	if (status & A4XX_INT0_CP_REG_PROTECT_FAULT) {
		uint32_t reg = gpu_read(gpu, REG_A4XX_CP_PROTECT_STATUS);
		printk("CP | Protected mode error| %s | addr=%x\n",
			reg & (1 << 24) ? "WRITE" : "READ",
			(reg & 0xFFFFF) >> 2);
	}

	gpu_write(gpu, REG_A4XX_RBBM_INT_CLEAR_CMD, status);

	msm_gpu_retire(gpu);

	return IRQ_HANDLED;
}