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
struct radeon_encoder_int_tmds {TYPE_1__* tmds_pll; } ;
struct TYPE_5__ {struct drm_device* dev; } ;
struct radeon_encoder {TYPE_2__ base; } ;
struct radeon_device {size_t family; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct TYPE_6__ {int /*<<< orphan*/  freq; int /*<<< orphan*/  value; } ;
struct TYPE_4__ {int /*<<< orphan*/  freq; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 TYPE_3__** default_tmds_pll ; 

bool radeon_legacy_get_tmds_info_from_table(struct radeon_encoder *encoder,
					    struct radeon_encoder_int_tmds *tmds)
{
	struct drm_device *dev = encoder->base.dev;
	struct radeon_device *rdev = dev->dev_private;
	int i;

	for (i = 0; i < 4; i++) {
		tmds->tmds_pll[i].value =
			default_tmds_pll[rdev->family][i].value;
		tmds->tmds_pll[i].freq = default_tmds_pll[rdev->family][i].freq;
	}

	return true;
}