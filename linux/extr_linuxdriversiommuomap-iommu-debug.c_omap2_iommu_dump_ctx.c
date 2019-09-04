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
struct omap_iommu {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM ; 
 int /*<<< orphan*/  CNTL ; 
 int /*<<< orphan*/  EMU_FAULT_AD ; 
 int /*<<< orphan*/  FAULT_AD ; 
 int /*<<< orphan*/  FLUSH_ENTRY ; 
 int /*<<< orphan*/  GFLUSH ; 
 int /*<<< orphan*/  IRQENABLE ; 
 int /*<<< orphan*/  IRQSTATUS ; 
 int /*<<< orphan*/  LD_TLB ; 
 int /*<<< orphan*/  LOCK ; 
 int /*<<< orphan*/  RAM ; 
 int /*<<< orphan*/  READ_CAM ; 
 int /*<<< orphan*/  READ_RAM ; 
 int /*<<< orphan*/  REVISION ; 
 int /*<<< orphan*/  TTB ; 
 int /*<<< orphan*/  WALKING_ST ; 
 int /*<<< orphan*/  pr_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
omap2_iommu_dump_ctx(struct omap_iommu *obj, char *buf, ssize_t len)
{
	char *p = buf;

	pr_reg(REVISION);
	pr_reg(IRQSTATUS);
	pr_reg(IRQENABLE);
	pr_reg(WALKING_ST);
	pr_reg(CNTL);
	pr_reg(FAULT_AD);
	pr_reg(TTB);
	pr_reg(LOCK);
	pr_reg(LD_TLB);
	pr_reg(CAM);
	pr_reg(RAM);
	pr_reg(GFLUSH);
	pr_reg(FLUSH_ENTRY);
	pr_reg(READ_CAM);
	pr_reg(READ_RAM);
	pr_reg(EMU_FAULT_AD);
out:
	return p - buf;
}