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
typedef  size_t u32 ;
struct komeda_dev {struct d71_dev* chip_data; } ;
struct d71_pipeline {int /*<<< orphan*/  dou_addr; int /*<<< orphan*/  lpu_addr; int /*<<< orphan*/  cu_addr; } ;
struct d71_dev {size_t num_pipelines; struct d71_pipeline** pipes; int /*<<< orphan*/  gcu_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_IRQ_MASK ; 
 int /*<<< orphan*/  ENABLED_CU_IRQS ; 
 int /*<<< orphan*/  ENABLED_DOU_IRQS ; 
 int /*<<< orphan*/  ENABLED_GCU_IRQS ; 
 int /*<<< orphan*/  ENABLED_LPU_IRQS ; 
 int /*<<< orphan*/  malidp_write32_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int d71_disable_irq(struct komeda_dev *mdev)
{
	struct d71_dev *d71 = mdev->chip_data;
	struct d71_pipeline *pipe;
	u32 i;

	malidp_write32_mask(d71->gcu_addr, BLK_IRQ_MASK, ENABLED_GCU_IRQS, 0);
	for (i = 0; i < d71->num_pipelines; i++) {
		pipe = d71->pipes[i];
		malidp_write32_mask(pipe->cu_addr,  BLK_IRQ_MASK,
				    ENABLED_CU_IRQS, 0);
		malidp_write32_mask(pipe->lpu_addr, BLK_IRQ_MASK,
				    ENABLED_LPU_IRQS, 0);
		malidp_write32_mask(pipe->dou_addr, BLK_IRQ_MASK,
				    ENABLED_DOU_IRQS, 0);
	}
	return 0;
}