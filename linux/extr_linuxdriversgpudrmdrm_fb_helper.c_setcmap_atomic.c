#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct fb_info {struct drm_fb_helper* par; } ;
struct fb_cmap {int start; int len; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct drm_property_blob {int color_mgmt_changed; int /*<<< orphan*/  gamma_lut; int /*<<< orphan*/  ctm; int /*<<< orphan*/  degamma_lut; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_fb_helper {int crtc_count; TYPE_2__* crtc_info; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;
struct drm_crtc_state {int color_mgmt_changed; int /*<<< orphan*/  gamma_lut; int /*<<< orphan*/  ctm; int /*<<< orphan*/  degamma_lut; } ;
struct drm_crtc {int gamma_size; int /*<<< orphan*/ * gamma_store; } ;
struct drm_atomic_state {struct drm_modeset_acquire_ctx* acquire_ctx; } ;
struct TYPE_3__ {struct drm_crtc* crtc; } ;
struct TYPE_4__ {TYPE_1__ mode_set; } ;

/* Variables and functions */
 int EDEADLK ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct drm_property_blob*) ; 
 int PTR_ERR (struct drm_property_blob*) ; 
 int drm_atomic_commit (struct drm_atomic_state*) ; 
 struct drm_property_blob* drm_atomic_get_crtc_state (struct drm_atomic_state*,struct drm_crtc*) ; 
 struct drm_atomic_state* drm_atomic_state_alloc (struct drm_device*) ; 
 int /*<<< orphan*/  drm_atomic_state_clear (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_state_put (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_fini (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_init (struct drm_modeset_acquire_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_backoff (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_drop_locks (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_property_blob_put (struct drm_property_blob*) ; 
 int drm_property_replace_blob (int /*<<< orphan*/ *,struct drm_property_blob*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct drm_property_blob* setcmap_new_gamma_lut (struct drm_crtc*,struct fb_cmap*) ; 

__attribute__((used)) static int setcmap_atomic(struct fb_cmap *cmap, struct fb_info *info)
{
	struct drm_fb_helper *fb_helper = info->par;
	struct drm_device *dev = fb_helper->dev;
	struct drm_property_blob *gamma_lut = NULL;
	struct drm_modeset_acquire_ctx ctx;
	struct drm_crtc_state *crtc_state;
	struct drm_atomic_state *state;
	struct drm_crtc *crtc;
	u16 *r, *g, *b;
	int i, ret = 0;
	bool replaced;

	drm_modeset_acquire_init(&ctx, 0);

	state = drm_atomic_state_alloc(dev);
	if (!state) {
		ret = -ENOMEM;
		goto out_ctx;
	}

	state->acquire_ctx = &ctx;
retry:
	for (i = 0; i < fb_helper->crtc_count; i++) {
		crtc = fb_helper->crtc_info[i].mode_set.crtc;

		if (!gamma_lut)
			gamma_lut = setcmap_new_gamma_lut(crtc, cmap);
		if (IS_ERR(gamma_lut)) {
			ret = PTR_ERR(gamma_lut);
			gamma_lut = NULL;
			goto out_state;
		}

		crtc_state = drm_atomic_get_crtc_state(state, crtc);
		if (IS_ERR(crtc_state)) {
			ret = PTR_ERR(crtc_state);
			goto out_state;
		}

		replaced  = drm_property_replace_blob(&crtc_state->degamma_lut,
						      NULL);
		replaced |= drm_property_replace_blob(&crtc_state->ctm, NULL);
		replaced |= drm_property_replace_blob(&crtc_state->gamma_lut,
						      gamma_lut);
		crtc_state->color_mgmt_changed |= replaced;
	}

	ret = drm_atomic_commit(state);
	if (ret)
		goto out_state;

	for (i = 0; i < fb_helper->crtc_count; i++) {
		crtc = fb_helper->crtc_info[i].mode_set.crtc;

		r = crtc->gamma_store;
		g = r + crtc->gamma_size;
		b = g + crtc->gamma_size;

		memcpy(r + cmap->start, cmap->red, cmap->len * sizeof(*r));
		memcpy(g + cmap->start, cmap->green, cmap->len * sizeof(*g));
		memcpy(b + cmap->start, cmap->blue, cmap->len * sizeof(*b));
	}

out_state:
	if (ret == -EDEADLK)
		goto backoff;

	drm_property_blob_put(gamma_lut);
	drm_atomic_state_put(state);
out_ctx:
	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	return ret;

backoff:
	drm_atomic_state_clear(state);
	drm_modeset_backoff(&ctx);
	goto retry;
}