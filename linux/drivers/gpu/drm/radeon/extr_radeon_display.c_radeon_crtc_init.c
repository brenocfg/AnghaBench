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
struct TYPE_4__ {struct radeon_crtc** crtcs; } ;
struct radeon_device {scalar_t__ family; scalar_t__ is_atom_bios; TYPE_1__ mode_info; } ;
struct TYPE_6__ {scalar_t__ num_connectors; struct drm_connector** connectors; int /*<<< orphan*/ * crtc; } ;
struct radeon_crtc {int crtc_id; int* lut_r; int* lut_g; int* lut_b; TYPE_3__ mode_set; int /*<<< orphan*/  base; int /*<<< orphan*/  max_cursor_height; int /*<<< orphan*/  max_cursor_width; int /*<<< orphan*/  flip_queue; } ;
struct TYPE_5__ {int /*<<< orphan*/  cursor_height; int /*<<< orphan*/  cursor_width; } ;
struct drm_device {TYPE_2__ mode_config; struct radeon_device* dev_private; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ CHIP_BONAIRE ; 
 int /*<<< orphan*/  CIK_CURSOR_HEIGHT ; 
 int /*<<< orphan*/  CIK_CURSOR_WIDTH ; 
 int /*<<< orphan*/  CURSOR_HEIGHT ; 
 int /*<<< orphan*/  CURSOR_WIDTH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RADEONFB_CONN_LIMIT ; 
 int /*<<< orphan*/  WQ_HIGHPRI ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_crtc_set_gamma_size (int /*<<< orphan*/ *,int) ; 
 struct radeon_crtc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_atombios_init_crtc (struct drm_device*,struct radeon_crtc*) ; 
 int /*<<< orphan*/  radeon_crtc_funcs ; 
 int /*<<< orphan*/  radeon_legacy_init_crtc (struct drm_device*,struct radeon_crtc*) ; 
 scalar_t__ radeon_r4xx_atom ; 

__attribute__((used)) static void radeon_crtc_init(struct drm_device *dev, int index)
{
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_crtc *radeon_crtc;
	int i;

	radeon_crtc = kzalloc(sizeof(struct radeon_crtc) + (RADEONFB_CONN_LIMIT * sizeof(struct drm_connector *)), GFP_KERNEL);
	if (radeon_crtc == NULL)
		return;

	drm_crtc_init(dev, &radeon_crtc->base, &radeon_crtc_funcs);

	drm_mode_crtc_set_gamma_size(&radeon_crtc->base, 256);
	radeon_crtc->crtc_id = index;
	radeon_crtc->flip_queue = alloc_workqueue("radeon-crtc", WQ_HIGHPRI, 0);
	rdev->mode_info.crtcs[index] = radeon_crtc;

	if (rdev->family >= CHIP_BONAIRE) {
		radeon_crtc->max_cursor_width = CIK_CURSOR_WIDTH;
		radeon_crtc->max_cursor_height = CIK_CURSOR_HEIGHT;
	} else {
		radeon_crtc->max_cursor_width = CURSOR_WIDTH;
		radeon_crtc->max_cursor_height = CURSOR_HEIGHT;
	}
	dev->mode_config.cursor_width = radeon_crtc->max_cursor_width;
	dev->mode_config.cursor_height = radeon_crtc->max_cursor_height;

#if 0
	radeon_crtc->mode_set.crtc = &radeon_crtc->base;
	radeon_crtc->mode_set.connectors = (struct drm_connector **)(radeon_crtc + 1);
	radeon_crtc->mode_set.num_connectors = 0;
#endif

	for (i = 0; i < 256; i++) {
		radeon_crtc->lut_r[i] = i << 2;
		radeon_crtc->lut_g[i] = i << 2;
		radeon_crtc->lut_b[i] = i << 2;
	}

	if (rdev->is_atom_bios && (ASIC_IS_AVIVO(rdev) || radeon_r4xx_atom))
		radeon_atombios_init_crtc(dev, radeon_crtc);
	else
		radeon_legacy_init_crtc(dev, radeon_crtc);
}