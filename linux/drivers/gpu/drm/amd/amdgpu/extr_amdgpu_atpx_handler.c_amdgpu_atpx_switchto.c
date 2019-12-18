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
typedef  int /*<<< orphan*/  u16 ;
typedef  enum vga_switcheroo_client_id { ____Placeholder_vga_switcheroo_client_id } vga_switcheroo_client_id ;
struct TYPE_2__ {int /*<<< orphan*/  atpx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATPX_DISCRETE_GPU ; 
 int /*<<< orphan*/  ATPX_INTEGRATED_GPU ; 
 int VGA_SWITCHEROO_IGD ; 
 TYPE_1__ amdgpu_atpx_priv ; 
 int /*<<< orphan*/  amdgpu_atpx_switch_disp_mux (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atpx_switch_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atpx_switch_i2c_mux (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atpx_switch_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_atpx_switchto(enum vga_switcheroo_client_id id)
{
	u16 gpu_id;

	if (id == VGA_SWITCHEROO_IGD)
		gpu_id = ATPX_INTEGRATED_GPU;
	else
		gpu_id = ATPX_DISCRETE_GPU;

	amdgpu_atpx_switch_start(&amdgpu_atpx_priv.atpx, gpu_id);
	amdgpu_atpx_switch_disp_mux(&amdgpu_atpx_priv.atpx, gpu_id);
	amdgpu_atpx_switch_i2c_mux(&amdgpu_atpx_priv.atpx, gpu_id);
	amdgpu_atpx_switch_end(&amdgpu_atpx_priv.atpx, gpu_id);

	return 0;
}