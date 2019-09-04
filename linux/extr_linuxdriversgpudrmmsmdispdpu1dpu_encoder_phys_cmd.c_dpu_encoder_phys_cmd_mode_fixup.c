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
 int /*<<< orphan*/  DPU_DEBUG_CMDENC (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  to_dpu_encoder_phys_cmd (struct dpu_encoder_phys*) ; 

__attribute__((used)) static bool dpu_encoder_phys_cmd_mode_fixup(
		struct dpu_encoder_phys *phys_enc,
		const struct drm_display_mode *mode,
		struct drm_display_mode *adj_mode)
{
	if (phys_enc)
		DPU_DEBUG_CMDENC(to_dpu_encoder_phys_cmd(phys_enc), "\n");
	return true;
}