#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/ * macrotile_mode_array; int /*<<< orphan*/ * tile_mode_array; int /*<<< orphan*/  mc_arb_ramcfg; int /*<<< orphan*/  gb_addr_config; TYPE_1__** rb_config; } ;
struct TYPE_6__ {TYPE_2__ config; } ;
struct amdgpu_device {TYPE_3__ gfx; int /*<<< orphan*/  grbm_idx_mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  raster_config_1; int /*<<< orphan*/  raster_config; int /*<<< orphan*/  user_rb_backend_disable; int /*<<< orphan*/  rb_backend_disable; } ;

/* Variables and functions */
 int /*<<< orphan*/  RREG32 (int) ; 
 int /*<<< orphan*/  amdgpu_gfx_select_se_sh (struct amdgpu_device*,int,int,int) ; 
#define  mmCC_RB_BACKEND_DISABLE 181 
#define  mmGB_ADDR_CONFIG 180 
#define  mmGB_MACROTILE_MODE0 179 
#define  mmGB_MACROTILE_MODE1 178 
#define  mmGB_MACROTILE_MODE10 177 
#define  mmGB_MACROTILE_MODE11 176 
#define  mmGB_MACROTILE_MODE12 175 
#define  mmGB_MACROTILE_MODE13 174 
#define  mmGB_MACROTILE_MODE14 173 
#define  mmGB_MACROTILE_MODE15 172 
#define  mmGB_MACROTILE_MODE2 171 
#define  mmGB_MACROTILE_MODE3 170 
#define  mmGB_MACROTILE_MODE4 169 
#define  mmGB_MACROTILE_MODE5 168 
#define  mmGB_MACROTILE_MODE6 167 
#define  mmGB_MACROTILE_MODE7 166 
#define  mmGB_MACROTILE_MODE8 165 
#define  mmGB_MACROTILE_MODE9 164 
#define  mmGB_TILE_MODE0 163 
#define  mmGB_TILE_MODE1 162 
#define  mmGB_TILE_MODE10 161 
#define  mmGB_TILE_MODE11 160 
#define  mmGB_TILE_MODE12 159 
#define  mmGB_TILE_MODE13 158 
#define  mmGB_TILE_MODE14 157 
#define  mmGB_TILE_MODE15 156 
#define  mmGB_TILE_MODE16 155 
#define  mmGB_TILE_MODE17 154 
#define  mmGB_TILE_MODE18 153 
#define  mmGB_TILE_MODE19 152 
#define  mmGB_TILE_MODE2 151 
#define  mmGB_TILE_MODE20 150 
#define  mmGB_TILE_MODE21 149 
#define  mmGB_TILE_MODE22 148 
#define  mmGB_TILE_MODE23 147 
#define  mmGB_TILE_MODE24 146 
#define  mmGB_TILE_MODE25 145 
#define  mmGB_TILE_MODE26 144 
#define  mmGB_TILE_MODE27 143 
#define  mmGB_TILE_MODE28 142 
#define  mmGB_TILE_MODE29 141 
#define  mmGB_TILE_MODE3 140 
#define  mmGB_TILE_MODE30 139 
#define  mmGB_TILE_MODE31 138 
#define  mmGB_TILE_MODE4 137 
#define  mmGB_TILE_MODE5 136 
#define  mmGB_TILE_MODE6 135 
#define  mmGB_TILE_MODE7 134 
#define  mmGB_TILE_MODE8 133 
#define  mmGB_TILE_MODE9 132 
#define  mmGC_USER_RB_BACKEND_DISABLE 131 
#define  mmMC_ARB_RAMCFG 130 
#define  mmPA_SC_RASTER_CONFIG 129 
#define  mmPA_SC_RASTER_CONFIG_1 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t vi_get_register_value(struct amdgpu_device *adev,
				      bool indexed, u32 se_num,
				      u32 sh_num, u32 reg_offset)
{
	if (indexed) {
		uint32_t val;
		unsigned se_idx = (se_num == 0xffffffff) ? 0 : se_num;
		unsigned sh_idx = (sh_num == 0xffffffff) ? 0 : sh_num;

		switch (reg_offset) {
		case mmCC_RB_BACKEND_DISABLE:
			return adev->gfx.config.rb_config[se_idx][sh_idx].rb_backend_disable;
		case mmGC_USER_RB_BACKEND_DISABLE:
			return adev->gfx.config.rb_config[se_idx][sh_idx].user_rb_backend_disable;
		case mmPA_SC_RASTER_CONFIG:
			return adev->gfx.config.rb_config[se_idx][sh_idx].raster_config;
		case mmPA_SC_RASTER_CONFIG_1:
			return adev->gfx.config.rb_config[se_idx][sh_idx].raster_config_1;
		}

		mutex_lock(&adev->grbm_idx_mutex);
		if (se_num != 0xffffffff || sh_num != 0xffffffff)
			amdgpu_gfx_select_se_sh(adev, se_num, sh_num, 0xffffffff);

		val = RREG32(reg_offset);

		if (se_num != 0xffffffff || sh_num != 0xffffffff)
			amdgpu_gfx_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
		mutex_unlock(&adev->grbm_idx_mutex);
		return val;
	} else {
		unsigned idx;

		switch (reg_offset) {
		case mmGB_ADDR_CONFIG:
			return adev->gfx.config.gb_addr_config;
		case mmMC_ARB_RAMCFG:
			return adev->gfx.config.mc_arb_ramcfg;
		case mmGB_TILE_MODE0:
		case mmGB_TILE_MODE1:
		case mmGB_TILE_MODE2:
		case mmGB_TILE_MODE3:
		case mmGB_TILE_MODE4:
		case mmGB_TILE_MODE5:
		case mmGB_TILE_MODE6:
		case mmGB_TILE_MODE7:
		case mmGB_TILE_MODE8:
		case mmGB_TILE_MODE9:
		case mmGB_TILE_MODE10:
		case mmGB_TILE_MODE11:
		case mmGB_TILE_MODE12:
		case mmGB_TILE_MODE13:
		case mmGB_TILE_MODE14:
		case mmGB_TILE_MODE15:
		case mmGB_TILE_MODE16:
		case mmGB_TILE_MODE17:
		case mmGB_TILE_MODE18:
		case mmGB_TILE_MODE19:
		case mmGB_TILE_MODE20:
		case mmGB_TILE_MODE21:
		case mmGB_TILE_MODE22:
		case mmGB_TILE_MODE23:
		case mmGB_TILE_MODE24:
		case mmGB_TILE_MODE25:
		case mmGB_TILE_MODE26:
		case mmGB_TILE_MODE27:
		case mmGB_TILE_MODE28:
		case mmGB_TILE_MODE29:
		case mmGB_TILE_MODE30:
		case mmGB_TILE_MODE31:
			idx = (reg_offset - mmGB_TILE_MODE0);
			return adev->gfx.config.tile_mode_array[idx];
		case mmGB_MACROTILE_MODE0:
		case mmGB_MACROTILE_MODE1:
		case mmGB_MACROTILE_MODE2:
		case mmGB_MACROTILE_MODE3:
		case mmGB_MACROTILE_MODE4:
		case mmGB_MACROTILE_MODE5:
		case mmGB_MACROTILE_MODE6:
		case mmGB_MACROTILE_MODE7:
		case mmGB_MACROTILE_MODE8:
		case mmGB_MACROTILE_MODE9:
		case mmGB_MACROTILE_MODE10:
		case mmGB_MACROTILE_MODE11:
		case mmGB_MACROTILE_MODE12:
		case mmGB_MACROTILE_MODE13:
		case mmGB_MACROTILE_MODE14:
		case mmGB_MACROTILE_MODE15:
			idx = (reg_offset - mmGB_MACROTILE_MODE0);
			return adev->gfx.config.macrotile_mode_array[idx];
		default:
			return RREG32(reg_offset);
		}
	}
}