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
struct drm_display_mode {int dummy; } ;
struct dpu_encoder_phys {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_VIDENC (struct dpu_encoder_phys*,char*) ; 

__attribute__((used)) static bool dpu_encoder_phys_vid_mode_fixup(
		struct dpu_encoder_phys *phys_enc,
		const struct drm_display_mode *mode,
		struct drm_display_mode *adj_mode)
{
	if (phys_enc)
		DPU_DEBUG_VIDENC(phys_enc, "\n");

	/*
	 * Modifying mode has consequences when the mode comes back to us
	 */
	return true;
}