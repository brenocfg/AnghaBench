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
 int A5XX_CP_INT_CP_AHB_ERROR ; 
 int A5XX_CP_INT_CP_DMA_ERROR ; 
 int A5XX_CP_INT_CP_HW_FAULT_ERROR ; 
 int A5XX_CP_INT_CP_OPCODE_ERROR ; 
 int A5XX_CP_INT_CP_REGISTER_PROTECTION_ERROR ; 
 int /*<<< orphan*/  REG_A5XX_CP_AHB_FAULT ; 
 int /*<<< orphan*/  REG_A5XX_CP_HW_FAULT ; 
 int /*<<< orphan*/  REG_A5XX_CP_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  REG_A5XX_CP_PFP_STAT_ADDR ; 
 int /*<<< orphan*/  REG_A5XX_CP_PFP_STAT_DATA ; 
 int /*<<< orphan*/  REG_A5XX_CP_PROTECT_STATUS ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,...) ; 
 int gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void a5xx_cp_err_irq(struct msm_gpu *gpu)
{
	u32 status = gpu_read(gpu, REG_A5XX_CP_INTERRUPT_STATUS);

	if (status & A5XX_CP_INT_CP_OPCODE_ERROR) {
		u32 val;

		gpu_write(gpu, REG_A5XX_CP_PFP_STAT_ADDR, 0);

		/*
		 * REG_A5XX_CP_PFP_STAT_DATA is indexed, and we want index 1 so
		 * read it twice
		 */

		gpu_read(gpu, REG_A5XX_CP_PFP_STAT_DATA);
		val = gpu_read(gpu, REG_A5XX_CP_PFP_STAT_DATA);

		dev_err_ratelimited(gpu->dev->dev, "CP | opcode error | possible opcode=0x%8.8X\n",
			val);
	}

	if (status & A5XX_CP_INT_CP_HW_FAULT_ERROR)
		dev_err_ratelimited(gpu->dev->dev, "CP | HW fault | status=0x%8.8X\n",
			gpu_read(gpu, REG_A5XX_CP_HW_FAULT));

	if (status & A5XX_CP_INT_CP_DMA_ERROR)
		dev_err_ratelimited(gpu->dev->dev, "CP | DMA error\n");

	if (status & A5XX_CP_INT_CP_REGISTER_PROTECTION_ERROR) {
		u32 val = gpu_read(gpu, REG_A5XX_CP_PROTECT_STATUS);

		dev_err_ratelimited(gpu->dev->dev,
			"CP | protected mode error | %s | addr=0x%8.8X | status=0x%8.8X\n",
			val & (1 << 24) ? "WRITE" : "READ",
			(val & 0xFFFFF) >> 2, val);
	}

	if (status & A5XX_CP_INT_CP_AHB_ERROR) {
		u32 status = gpu_read(gpu, REG_A5XX_CP_AHB_FAULT);
		const char *access[16] = { "reserved", "reserved",
			"timestamp lo", "timestamp hi", "pfp read", "pfp write",
			"", "", "me read", "me write", "", "", "crashdump read",
			"crashdump write" };

		dev_err_ratelimited(gpu->dev->dev,
			"CP | AHB error | addr=%X access=%s error=%d | status=0x%8.8X\n",
			status & 0xFFFFF, access[(status >> 24) & 0xF],
			(status & (1 << 31)), status);
	}
}