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
struct radeon_encoder_ext_tmds {int dummy; } ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct radeon_encoder {TYPE_1__ base; } ;
struct radeon_device {scalar_t__ is_atom_bios; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct radeon_encoder_ext_tmds* kzalloc (int,int /*<<< orphan*/ ) ; 
 int radeon_legacy_get_ext_tmds_info_from_combios (struct radeon_encoder*,struct radeon_encoder_ext_tmds*) ; 
 int /*<<< orphan*/  radeon_legacy_get_ext_tmds_info_from_table (struct radeon_encoder*,struct radeon_encoder_ext_tmds*) ; 

__attribute__((used)) static struct radeon_encoder_ext_tmds *radeon_legacy_get_ext_tmds_info(struct radeon_encoder *encoder)
{
	struct drm_device *dev = encoder->base.dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder_ext_tmds *tmds = NULL;
	bool ret;

	if (rdev->is_atom_bios)
		return NULL;

	tmds = kzalloc(sizeof(struct radeon_encoder_ext_tmds), GFP_KERNEL);

	if (!tmds)
		return NULL;

	ret = radeon_legacy_get_ext_tmds_info_from_combios(encoder, tmds);

	if (ret == false)
		radeon_legacy_get_ext_tmds_info_from_table(encoder, tmds);

	return tmds;
}