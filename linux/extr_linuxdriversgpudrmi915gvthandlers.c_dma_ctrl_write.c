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
typedef  int /*<<< orphan*/  u32 ;
struct intel_vgpu {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ GFX_MODE_BIT_SET_IN_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_DMA ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgpu_vreg (struct intel_vgpu*,unsigned int) ; 
 int /*<<< orphan*/  write_vreg (struct intel_vgpu*,unsigned int,void*,unsigned int) ; 

__attribute__((used)) static int dma_ctrl_write(struct intel_vgpu *vgpu, unsigned int offset,
		void *p_data, unsigned int bytes)
{
	u32 mode;

	write_vreg(vgpu, offset, p_data, bytes);
	mode = vgpu_vreg(vgpu, offset);

	if (GFX_MODE_BIT_SET_IN_MASK(mode, START_DMA)) {
		WARN_ONCE(1, "VM(%d): iGVT-g doesn't support GuC\n",
				vgpu->id);
		return 0;
	}

	return 0;
}