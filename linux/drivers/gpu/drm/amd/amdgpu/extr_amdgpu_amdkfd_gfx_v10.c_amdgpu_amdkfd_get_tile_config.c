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
struct tile_config {void* num_macro_tile_configs; int /*<<< orphan*/  macro_tile_config_ptr; void* num_tile_configs; int /*<<< orphan*/  tile_config_ptr; void* num_ranks; void* num_banks; int /*<<< orphan*/  gb_addr_config; } ;
struct kgd_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  macrotile_mode_array; int /*<<< orphan*/  tile_mode_array; int /*<<< orphan*/  mc_arb_ramcfg; int /*<<< orphan*/  gb_addr_config; } ;
struct TYPE_4__ {TYPE_1__ config; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 void* ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MC_ARB_RAMCFG ; 
 int /*<<< orphan*/  NOOFBANK ; 
 int /*<<< orphan*/  NOOFRANKS ; 
 void* REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_amdkfd_get_tile_config(struct kgd_dev *kgd,
		struct tile_config *config)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)kgd;

	config->gb_addr_config = adev->gfx.config.gb_addr_config;
#if 0
/* TODO - confirm REG_GET_FIELD x2, should be OK as is... but
 * MC_ARB_RAMCFG register doesn't exist on Vega10 - initial amdgpu
 * changes commented out related code, doing the same here for now but
 * need to sync with Ken et al
 */
	config->num_banks = REG_GET_FIELD(adev->gfx.config.mc_arb_ramcfg,
				MC_ARB_RAMCFG, NOOFBANK);
	config->num_ranks = REG_GET_FIELD(adev->gfx.config.mc_arb_ramcfg,
				MC_ARB_RAMCFG, NOOFRANKS);
#endif

	config->tile_config_ptr = adev->gfx.config.tile_mode_array;
	config->num_tile_configs =
			ARRAY_SIZE(adev->gfx.config.tile_mode_array);
	config->macro_tile_config_ptr =
			adev->gfx.config.macrotile_mode_array;
	config->num_macro_tile_configs =
			ARRAY_SIZE(adev->gfx.config.macrotile_mode_array);

	return 0;
}