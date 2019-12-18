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
typedef  int u8 ;
struct mtk_vpu {TYPE_1__* extmem; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pa; int /*<<< orphan*/  va; } ;

/* Variables and functions */
 size_t VPU_EXT_D_SIZE ; 
 size_t VPU_EXT_P_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vpu_free_ext_mem(struct mtk_vpu *vpu, u8 fw_type)
{
	struct device *dev = vpu->dev;
	size_t fw_ext_size = fw_type ? VPU_EXT_D_SIZE : VPU_EXT_P_SIZE;

	dma_free_coherent(dev, fw_ext_size, vpu->extmem[fw_type].va,
			  vpu->extmem[fw_type].pa);
}