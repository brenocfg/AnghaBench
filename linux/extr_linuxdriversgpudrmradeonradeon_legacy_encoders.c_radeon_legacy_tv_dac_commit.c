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
struct radeon_device {scalar_t__ is_atom_bios; } ;
struct drm_encoder {TYPE_1__* dev; } ;
struct TYPE_2__ {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  radeon_atom_output_lock (struct drm_encoder*,int) ; 
 int /*<<< orphan*/  radeon_combios_output_lock (struct drm_encoder*,int) ; 
 int /*<<< orphan*/  radeon_legacy_tv_dac_dpms (struct drm_encoder*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void radeon_legacy_tv_dac_commit(struct drm_encoder *encoder)
{
	struct radeon_device *rdev = encoder->dev->dev_private;

	radeon_legacy_tv_dac_dpms(encoder, DRM_MODE_DPMS_ON);

	if (rdev->is_atom_bios)
		radeon_atom_output_lock(encoder, true);
	else
		radeon_combios_output_lock(encoder, true);
}