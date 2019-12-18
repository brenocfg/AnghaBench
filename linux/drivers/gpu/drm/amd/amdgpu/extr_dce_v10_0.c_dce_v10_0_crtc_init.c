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
struct drm_connector {int dummy; } ;
struct TYPE_4__ {struct amdgpu_crtc** crtcs; } ;
struct amdgpu_device {TYPE_3__* ddev; TYPE_1__ mode_info; } ;
struct amdgpu_crtc {int crtc_id; int max_cursor_width; int max_cursor_height; int /*<<< orphan*/  base; int /*<<< orphan*/ * connector; int /*<<< orphan*/ * encoder; scalar_t__ adjusted_clock; int /*<<< orphan*/  pll_id; int /*<<< orphan*/  crtc_offset; } ;
struct TYPE_5__ {int cursor_width; int cursor_height; } ;
struct TYPE_6__ {TYPE_2__ mode_config; } ;

/* Variables and functions */
 int AMDGPUFB_CONN_LIMIT ; 
 int /*<<< orphan*/  ATOM_PPLL_INVALID ; 
 int /*<<< orphan*/  CRTC0_REGISTER_OFFSET ; 
 int /*<<< orphan*/  CRTC1_REGISTER_OFFSET ; 
 int /*<<< orphan*/  CRTC2_REGISTER_OFFSET ; 
 int /*<<< orphan*/  CRTC3_REGISTER_OFFSET ; 
 int /*<<< orphan*/  CRTC4_REGISTER_OFFSET ; 
 int /*<<< orphan*/  CRTC5_REGISTER_OFFSET ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dce_v10_0_crtc_funcs ; 
 int /*<<< orphan*/  dce_v10_0_crtc_helper_funcs ; 
 int /*<<< orphan*/  drm_crtc_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_init (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_crtc_set_gamma_size (int /*<<< orphan*/ *,int) ; 
 struct amdgpu_crtc* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dce_v10_0_crtc_init(struct amdgpu_device *adev, int index)
{
	struct amdgpu_crtc *amdgpu_crtc;

	amdgpu_crtc = kzalloc(sizeof(struct amdgpu_crtc) +
			      (AMDGPUFB_CONN_LIMIT * sizeof(struct drm_connector *)), GFP_KERNEL);
	if (amdgpu_crtc == NULL)
		return -ENOMEM;

	drm_crtc_init(adev->ddev, &amdgpu_crtc->base, &dce_v10_0_crtc_funcs);

	drm_mode_crtc_set_gamma_size(&amdgpu_crtc->base, 256);
	amdgpu_crtc->crtc_id = index;
	adev->mode_info.crtcs[index] = amdgpu_crtc;

	amdgpu_crtc->max_cursor_width = 128;
	amdgpu_crtc->max_cursor_height = 128;
	adev->ddev->mode_config.cursor_width = amdgpu_crtc->max_cursor_width;
	adev->ddev->mode_config.cursor_height = amdgpu_crtc->max_cursor_height;

	switch (amdgpu_crtc->crtc_id) {
	case 0:
	default:
		amdgpu_crtc->crtc_offset = CRTC0_REGISTER_OFFSET;
		break;
	case 1:
		amdgpu_crtc->crtc_offset = CRTC1_REGISTER_OFFSET;
		break;
	case 2:
		amdgpu_crtc->crtc_offset = CRTC2_REGISTER_OFFSET;
		break;
	case 3:
		amdgpu_crtc->crtc_offset = CRTC3_REGISTER_OFFSET;
		break;
	case 4:
		amdgpu_crtc->crtc_offset = CRTC4_REGISTER_OFFSET;
		break;
	case 5:
		amdgpu_crtc->crtc_offset = CRTC5_REGISTER_OFFSET;
		break;
	}

	amdgpu_crtc->pll_id = ATOM_PPLL_INVALID;
	amdgpu_crtc->adjusted_clock = 0;
	amdgpu_crtc->encoder = NULL;
	amdgpu_crtc->connector = NULL;
	drm_crtc_helper_add(&amdgpu_crtc->base, &dce_v10_0_crtc_helper_funcs);

	return 0;
}