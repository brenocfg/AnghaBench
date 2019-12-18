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
struct msm_gpu {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int A6XX_CP_INT_CP_AHB_ERROR ; 
 int A6XX_CP_INT_CP_HW_FAULT_ERROR ; 
 int A6XX_CP_INT_CP_ILLEGAL_INSTR_ERROR ; 
 int A6XX_CP_INT_CP_OPCODE_ERROR ; 
 int A6XX_CP_INT_CP_REGISTER_PROTECTION_ERROR ; 
 int A6XX_CP_INT_CP_UCODE_ERROR ; 
 int A6XX_CP_INT_CP_VSD_PARITY_ERROR ; 
 int /*<<< orphan*/  REG_A6XX_CP_HW_FAULT ; 
 int /*<<< orphan*/  REG_A6XX_CP_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  REG_A6XX_CP_PROTECT_STATUS ; 
 int /*<<< orphan*/  REG_A6XX_CP_SQE_STAT_ADDR ; 
 int /*<<< orphan*/  REG_A6XX_CP_SQE_STAT_DATA ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ *,char*,...) ; 
 int gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void a6xx_cp_hw_err_irq(struct msm_gpu *gpu)
{
	u32 status = gpu_read(gpu, REG_A6XX_CP_INTERRUPT_STATUS);

	if (status & A6XX_CP_INT_CP_OPCODE_ERROR) {
		u32 val;

		gpu_write(gpu, REG_A6XX_CP_SQE_STAT_ADDR, 1);
		val = gpu_read(gpu, REG_A6XX_CP_SQE_STAT_DATA);
		dev_err_ratelimited(&gpu->pdev->dev,
			"CP | opcode error | possible opcode=0x%8.8X\n",
			val);
	}

	if (status & A6XX_CP_INT_CP_UCODE_ERROR)
		dev_err_ratelimited(&gpu->pdev->dev,
			"CP ucode error interrupt\n");

	if (status & A6XX_CP_INT_CP_HW_FAULT_ERROR)
		dev_err_ratelimited(&gpu->pdev->dev, "CP | HW fault | status=0x%8.8X\n",
			gpu_read(gpu, REG_A6XX_CP_HW_FAULT));

	if (status & A6XX_CP_INT_CP_REGISTER_PROTECTION_ERROR) {
		u32 val = gpu_read(gpu, REG_A6XX_CP_PROTECT_STATUS);

		dev_err_ratelimited(&gpu->pdev->dev,
			"CP | protected mode error | %s | addr=0x%8.8X | status=0x%8.8X\n",
			val & (1 << 20) ? "READ" : "WRITE",
			(val & 0x3ffff), val);
	}

	if (status & A6XX_CP_INT_CP_AHB_ERROR)
		dev_err_ratelimited(&gpu->pdev->dev, "CP AHB error interrupt\n");

	if (status & A6XX_CP_INT_CP_VSD_PARITY_ERROR)
		dev_err_ratelimited(&gpu->pdev->dev, "CP VSD decoder parity error\n");

	if (status & A6XX_CP_INT_CP_ILLEGAL_INSTR_ERROR)
		dev_err_ratelimited(&gpu->pdev->dev, "CP illegal instruction error\n");

}