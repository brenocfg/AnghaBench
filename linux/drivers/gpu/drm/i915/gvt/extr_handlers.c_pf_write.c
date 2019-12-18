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
typedef  int u32 ;
struct intel_vgpu {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int PS_PLANE_SEL_MASK ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ) ; 
 unsigned int _PS_1A_CTRL ; 
 unsigned int _PS_1B_CTRL ; 
 unsigned int _PS_1C_CTRL ; 
 unsigned int _PS_2A_CTRL ; 
 unsigned int _PS_2B_CTRL ; 
 int intel_vgpu_default_mmio_write (struct intel_vgpu*,unsigned int,void*,unsigned int) ; 

__attribute__((used)) static int pf_write(struct intel_vgpu *vgpu,
		unsigned int offset, void *p_data, unsigned int bytes)
{
	u32 val = *(u32 *)p_data;

	if ((offset == _PS_1A_CTRL || offset == _PS_2A_CTRL ||
	   offset == _PS_1B_CTRL || offset == _PS_2B_CTRL ||
	   offset == _PS_1C_CTRL) && (val & PS_PLANE_SEL_MASK) != 0) {
		WARN_ONCE(true, "VM(%d): guest is trying to scaling a plane\n",
			  vgpu->id);
		return 0;
	}

	return intel_vgpu_default_mmio_write(vgpu, offset, p_data, bytes);
}