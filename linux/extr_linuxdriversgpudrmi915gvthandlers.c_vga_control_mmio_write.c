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
struct intel_vgpu {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int VGA_DISP_DISABLE ; 
 int /*<<< orphan*/  gvt_dbg_core (char*,int /*<<< orphan*/ ,char*) ; 
 int vgpu_vreg (struct intel_vgpu*,unsigned int) ; 
 int /*<<< orphan*/  write_vreg (struct intel_vgpu*,unsigned int,void*,unsigned int) ; 

__attribute__((used)) static int vga_control_mmio_write(struct intel_vgpu *vgpu, unsigned int offset,
		void *p_data, unsigned int bytes)
{
	bool vga_disable;

	write_vreg(vgpu, offset, p_data, bytes);
	vga_disable = vgpu_vreg(vgpu, offset) & VGA_DISP_DISABLE;

	gvt_dbg_core("vgpu%d: %s VGA mode\n", vgpu->id,
			vga_disable ? "Disable" : "Enable");
	return 0;
}