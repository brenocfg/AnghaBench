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
typedef  int u32 ;
struct msm_gpu {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int A5XX_RBBM_INT_0_MASK_RBBM_AHB_ERROR ; 
 int A5XX_RBBM_INT_0_MASK_RBBM_ATB_ASYNC_OVERFLOW ; 
 int A5XX_RBBM_INT_0_MASK_RBBM_ATB_BUS_OVERFLOW ; 
 int A5XX_RBBM_INT_0_MASK_RBBM_ETS_MS_TIMEOUT ; 
 int A5XX_RBBM_INT_0_MASK_RBBM_ME_MS_TIMEOUT ; 
 int A5XX_RBBM_INT_0_MASK_RBBM_PFP_MS_TIMEOUT ; 
 int A5XX_RBBM_INT_0_MASK_RBBM_TRANSFER_TIMEOUT ; 
 int /*<<< orphan*/  REG_A5XX_RBBM_AHB_CMD ; 
 int /*<<< orphan*/  REG_A5XX_RBBM_AHB_ERROR_STATUS ; 
 int /*<<< orphan*/  REG_A5XX_RBBM_AHB_ETS_SPLIT_STATUS ; 
 int /*<<< orphan*/  REG_A5XX_RBBM_AHB_ME_SPLIT_STATUS ; 
 int /*<<< orphan*/  REG_A5XX_RBBM_AHB_PFP_SPLIT_STATUS ; 
 int /*<<< orphan*/  REG_A5XX_RBBM_INT_CLEAR_CMD ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void a5xx_rbbm_err_irq(struct msm_gpu *gpu, u32 status)
{
	if (status & A5XX_RBBM_INT_0_MASK_RBBM_AHB_ERROR) {
		u32 val = gpu_read(gpu, REG_A5XX_RBBM_AHB_ERROR_STATUS);

		dev_err_ratelimited(gpu->dev->dev,
			"RBBM | AHB bus error | %s | addr=0x%X | ports=0x%X:0x%X\n",
			val & (1 << 28) ? "WRITE" : "READ",
			(val & 0xFFFFF) >> 2, (val >> 20) & 0x3,
			(val >> 24) & 0xF);

		/* Clear the error */
		gpu_write(gpu, REG_A5XX_RBBM_AHB_CMD, (1 << 4));

		/* Clear the interrupt */
		gpu_write(gpu, REG_A5XX_RBBM_INT_CLEAR_CMD,
			A5XX_RBBM_INT_0_MASK_RBBM_AHB_ERROR);
	}

	if (status & A5XX_RBBM_INT_0_MASK_RBBM_TRANSFER_TIMEOUT)
		dev_err_ratelimited(gpu->dev->dev, "RBBM | AHB transfer timeout\n");

	if (status & A5XX_RBBM_INT_0_MASK_RBBM_ME_MS_TIMEOUT)
		dev_err_ratelimited(gpu->dev->dev, "RBBM | ME master split | status=0x%X\n",
			gpu_read(gpu, REG_A5XX_RBBM_AHB_ME_SPLIT_STATUS));

	if (status & A5XX_RBBM_INT_0_MASK_RBBM_PFP_MS_TIMEOUT)
		dev_err_ratelimited(gpu->dev->dev, "RBBM | PFP master split | status=0x%X\n",
			gpu_read(gpu, REG_A5XX_RBBM_AHB_PFP_SPLIT_STATUS));

	if (status & A5XX_RBBM_INT_0_MASK_RBBM_ETS_MS_TIMEOUT)
		dev_err_ratelimited(gpu->dev->dev, "RBBM | ETS master split | status=0x%X\n",
			gpu_read(gpu, REG_A5XX_RBBM_AHB_ETS_SPLIT_STATUS));

	if (status & A5XX_RBBM_INT_0_MASK_RBBM_ATB_ASYNC_OVERFLOW)
		dev_err_ratelimited(gpu->dev->dev, "RBBM | ATB ASYNC overflow\n");

	if (status & A5XX_RBBM_INT_0_MASK_RBBM_ATB_BUS_OVERFLOW)
		dev_err_ratelimited(gpu->dev->dev, "RBBM | ATB bus overflow\n");
}