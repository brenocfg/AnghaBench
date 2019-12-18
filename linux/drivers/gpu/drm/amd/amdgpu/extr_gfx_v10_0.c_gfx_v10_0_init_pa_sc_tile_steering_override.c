#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u32 ;
struct TYPE_3__ {int max_shader_engines; int max_sh_per_se; int num_sc_per_sh; int num_packer_per_sc; } ;
struct TYPE_4__ {TYPE_1__ config; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int PA_SC_TILE_STEERING_OVERRIDE__NUM_PACKER_PER_SC_MASK ; 
 int PA_SC_TILE_STEERING_OVERRIDE__NUM_PACKER_PER_SC__SHIFT ; 
 int PA_SC_TILE_STEERING_OVERRIDE__NUM_RB_PER_SC_MASK ; 
 int PA_SC_TILE_STEERING_OVERRIDE__NUM_RB_PER_SC__SHIFT ; 
 int PA_SC_TILE_STEERING_OVERRIDE__NUM_SC_MASK ; 
 int PA_SC_TILE_STEERING_OVERRIDE__NUM_SC__SHIFT ; 
 int gfx_v10_0_get_rb_active_bitmap (struct amdgpu_device*) ; 
 int hweight32 (int) ; 
 int order_base_2 (int) ; 

__attribute__((used)) static u32 gfx_v10_0_init_pa_sc_tile_steering_override(struct amdgpu_device *adev)
{
	uint32_t num_sc;
	uint32_t enabled_rb_per_sh;
	uint32_t active_rb_bitmap;
	uint32_t num_rb_per_sc;
	uint32_t num_packer_per_sc;
	uint32_t pa_sc_tile_steering_override;

	/* init num_sc */
	num_sc = adev->gfx.config.max_shader_engines * adev->gfx.config.max_sh_per_se *
			adev->gfx.config.num_sc_per_sh;
	/* init num_rb_per_sc */
	active_rb_bitmap = gfx_v10_0_get_rb_active_bitmap(adev);
	enabled_rb_per_sh = hweight32(active_rb_bitmap);
	num_rb_per_sc = enabled_rb_per_sh / adev->gfx.config.num_sc_per_sh;
	/* init num_packer_per_sc */
	num_packer_per_sc = adev->gfx.config.num_packer_per_sc;

	pa_sc_tile_steering_override = 0;
	pa_sc_tile_steering_override |=
		(order_base_2(num_sc) << PA_SC_TILE_STEERING_OVERRIDE__NUM_SC__SHIFT) &
		PA_SC_TILE_STEERING_OVERRIDE__NUM_SC_MASK;
	pa_sc_tile_steering_override |=
		(order_base_2(num_rb_per_sc) << PA_SC_TILE_STEERING_OVERRIDE__NUM_RB_PER_SC__SHIFT) &
		PA_SC_TILE_STEERING_OVERRIDE__NUM_RB_PER_SC_MASK;
	pa_sc_tile_steering_override |=
		(order_base_2(num_packer_per_sc) << PA_SC_TILE_STEERING_OVERRIDE__NUM_PACKER_PER_SC__SHIFT) &
		PA_SC_TILE_STEERING_OVERRIDE__NUM_PACKER_PER_SC_MASK;

	return pa_sc_tile_steering_override;
}