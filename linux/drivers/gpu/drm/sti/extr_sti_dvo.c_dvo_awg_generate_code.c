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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_display_mode {scalar_t__ hsync_start; scalar_t__ htotal; scalar_t__ hdisplay; scalar_t__ vsync_start; scalar_t__ vtotal; scalar_t__ vdisplay; } ;
struct sti_dvo {struct dvo_config* config; struct drm_display_mode mode; } ;
struct dvo_config {scalar_t__ (* awg_fwgen_fct ) (struct awg_code_generation_params*,struct awg_timing*) ;} ;
struct awg_timing {int /*<<< orphan*/  blanking_level; scalar_t__ trailing_pixels; scalar_t__ blanking_pixels; scalar_t__ active_pixels; scalar_t__ total_pixels; scalar_t__ trailing_lines; scalar_t__ blanking_lines; scalar_t__ active_lines; scalar_t__ total_lines; } ;
struct awg_code_generation_params {scalar_t__ instruction_offset; int /*<<< orphan*/ * ram_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLANKING_LEVEL ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 scalar_t__ stub1 (struct awg_code_generation_params*,struct awg_timing*) ; 

__attribute__((used)) static int dvo_awg_generate_code(struct sti_dvo *dvo, u8 *ram_size, u32 *ram_code)
{
	struct drm_display_mode *mode = &dvo->mode;
	struct dvo_config *config = dvo->config;
	struct awg_code_generation_params fw_gen_params;
	struct awg_timing timing;

	fw_gen_params.ram_code = ram_code;
	fw_gen_params.instruction_offset = 0;

	timing.total_lines = mode->vtotal;
	timing.active_lines = mode->vdisplay;
	timing.blanking_lines = mode->vsync_start - mode->vdisplay;
	timing.trailing_lines = mode->vtotal - mode->vsync_start;
	timing.total_pixels = mode->htotal;
	timing.active_pixels = mode->hdisplay;
	timing.blanking_pixels = mode->hsync_start - mode->hdisplay;
	timing.trailing_pixels = mode->htotal - mode->hsync_start;
	timing.blanking_level = BLANKING_LEVEL;

	if (config->awg_fwgen_fct(&fw_gen_params, &timing)) {
		DRM_ERROR("AWG firmware not properly generated\n");
		return -EINVAL;
	}

	*ram_size = fw_gen_params.instruction_offset;

	return 0;
}