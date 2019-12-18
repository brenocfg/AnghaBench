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
struct mtk_vpu {TYPE_1__* extmem; scalar_t__ enable_4GB; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int pa; int /*<<< orphan*/  va; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int VPU_DMEM_EXT0_ADDR ; 
 int VPU_DMEM_EXT1_ADDR ; 
 size_t VPU_EXT_D_SIZE ; 
 size_t VPU_EXT_P_SIZE ; 
 int VPU_PMEM_EXT0_ADDR ; 
 int VPU_PMEM_EXT1_ADDR ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,size_t,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpu_cfg_writel (struct mtk_vpu*,int,int) ; 

__attribute__((used)) static int vpu_alloc_ext_mem(struct mtk_vpu *vpu, u32 fw_type)
{
	struct device *dev = vpu->dev;
	size_t fw_ext_size = fw_type ? VPU_EXT_D_SIZE : VPU_EXT_P_SIZE;
	u32 vpu_ext_mem0 = fw_type ? VPU_DMEM_EXT0_ADDR : VPU_PMEM_EXT0_ADDR;
	u32 vpu_ext_mem1 = fw_type ? VPU_DMEM_EXT1_ADDR : VPU_PMEM_EXT1_ADDR;
	u32 offset_4gb = vpu->enable_4GB ? 0x40000000 : 0;

	vpu->extmem[fw_type].va = dma_alloc_coherent(dev,
					       fw_ext_size,
					       &vpu->extmem[fw_type].pa,
					       GFP_KERNEL);
	if (!vpu->extmem[fw_type].va) {
		dev_err(dev, "Failed to allocate the extended program memory\n");
		return -ENOMEM;
	}

	/* Disable extend0. Enable extend1 */
	vpu_cfg_writel(vpu, 0x1, vpu_ext_mem0);
	vpu_cfg_writel(vpu, (vpu->extmem[fw_type].pa & 0xFFFFF000) + offset_4gb,
		       vpu_ext_mem1);

	dev_info(dev, "%s extend memory phy=0x%llx virt=0x%p\n",
		 fw_type ? "Data" : "Program",
		 (unsigned long long)vpu->extmem[fw_type].pa,
		 vpu->extmem[fw_type].va);

	return 0;
}