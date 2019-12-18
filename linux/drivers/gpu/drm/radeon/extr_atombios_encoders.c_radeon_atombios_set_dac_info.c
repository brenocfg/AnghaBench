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
struct radeon_encoder_atom_dac {int /*<<< orphan*/  tv_std; } ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct radeon_encoder {TYPE_1__ base; } ;
struct radeon_device {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct radeon_encoder_atom_dac* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_atombios_get_tv_info (struct radeon_device*) ; 

__attribute__((used)) static struct radeon_encoder_atom_dac *
radeon_atombios_set_dac_info(struct radeon_encoder *radeon_encoder)
{
	struct drm_device *dev = radeon_encoder->base.dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder_atom_dac *dac = kzalloc(sizeof(struct radeon_encoder_atom_dac), GFP_KERNEL);

	if (!dac)
		return NULL;

	dac->tv_std = radeon_atombios_get_tv_info(rdev);
	return dac;
}