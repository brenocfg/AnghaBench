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
struct tile_config {void* num_macro_tile_configs; int /*<<< orphan*/  macro_tile_config_ptr; void* num_tile_configs; int /*<<< orphan*/  tile_config_ptr; int /*<<< orphan*/  gb_addr_config; } ;
struct kgd_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  macrotile_mode_array; int /*<<< orphan*/  tile_mode_array; int /*<<< orphan*/  gb_addr_config; } ;
struct TYPE_3__ {TYPE_2__ config; } ;
struct amdgpu_device {TYPE_1__ gfx; } ;

/* Variables and functions */
 void* ARRAY_SIZE (int /*<<< orphan*/ ) ; 

int kgd_gfx_v9_get_tile_config(struct kgd_dev *kgd,
		struct tile_config *config)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)kgd;

	config->gb_addr_config = adev->gfx.config.gb_addr_config;

	config->tile_config_ptr = adev->gfx.config.tile_mode_array;
	config->num_tile_configs =
			ARRAY_SIZE(adev->gfx.config.tile_mode_array);
	config->macro_tile_config_ptr =
			adev->gfx.config.macrotile_mode_array;
	config->num_macro_tile_configs =
			ARRAY_SIZE(adev->gfx.config.macrotile_mode_array);

	return 0;
}