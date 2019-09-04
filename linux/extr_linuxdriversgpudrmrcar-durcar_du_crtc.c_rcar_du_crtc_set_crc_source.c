#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int source; unsigned int index; } ;
struct rcar_du_crtc_state {TYPE_5__ crc; } ;
struct rcar_du_crtc {TYPE_4__* vsp; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;
struct drm_atomic_state {struct drm_modeset_acquire_ctx* acquire_ctx; } ;
typedef  enum vsp1_du_crc_source { ____Placeholder_vsp1_du_crc_source } vsp1_du_crc_source ;
struct TYPE_9__ {unsigned int num_planes; TYPE_3__* planes; } ;
struct TYPE_6__ {unsigned int id; } ;
struct TYPE_7__ {TYPE_1__ base; } ;
struct TYPE_8__ {TYPE_2__ plane; } ;

/* Variables and functions */
 int EDEADLK ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IS_ERR (struct drm_crtc_state*) ; 
 int PTR_ERR (struct drm_crtc_state*) ; 
 int VSP1_DU_CRC_NONE ; 
 int VSP1_DU_CRC_OUTPUT ; 
 int VSP1_DU_CRC_PLANE ; 
 int drm_atomic_commit (struct drm_atomic_state*) ; 
 struct drm_crtc_state* drm_atomic_get_crtc_state (struct drm_atomic_state*,struct drm_crtc*) ; 
 struct drm_atomic_state* drm_atomic_state_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_atomic_state_clear (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_state_put (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_fini (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_init (struct drm_modeset_acquire_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_backoff (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_drop_locks (struct drm_modeset_acquire_ctx*) ; 
 int kstrtouint (char const*,int,unsigned int*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strstarts (char const*,char*) ; 
 struct rcar_du_crtc* to_rcar_crtc (struct drm_crtc*) ; 
 struct rcar_du_crtc_state* to_rcar_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static int rcar_du_crtc_set_crc_source(struct drm_crtc *crtc,
				       const char *source_name,
				       size_t *values_cnt)
{
	struct rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);
	struct drm_modeset_acquire_ctx ctx;
	struct drm_crtc_state *crtc_state;
	struct drm_atomic_state *state;
	enum vsp1_du_crc_source source;
	unsigned int index = 0;
	unsigned int i;
	int ret;

	/*
	 * Parse the source name. Supported values are "plane%u" to compute the
	 * CRC on an input plane (%u is the plane ID), and "auto" to compute the
	 * CRC on the composer (VSP) output.
	 */
	if (!source_name) {
		source = VSP1_DU_CRC_NONE;
	} else if (!strcmp(source_name, "auto")) {
		source = VSP1_DU_CRC_OUTPUT;
	} else if (strstarts(source_name, "plane")) {
		source = VSP1_DU_CRC_PLANE;

		ret = kstrtouint(source_name + strlen("plane"), 10, &index);
		if (ret < 0)
			return ret;

		for (i = 0; i < rcrtc->vsp->num_planes; ++i) {
			if (index == rcrtc->vsp->planes[i].plane.base.id) {
				index = i;
				break;
			}
		}

		if (i >= rcrtc->vsp->num_planes)
			return -EINVAL;
	} else {
		return -EINVAL;
	}

	*values_cnt = 1;

	/* Perform an atomic commit to set the CRC source. */
	drm_modeset_acquire_init(&ctx, 0);

	state = drm_atomic_state_alloc(crtc->dev);
	if (!state) {
		ret = -ENOMEM;
		goto unlock;
	}

	state->acquire_ctx = &ctx;

retry:
	crtc_state = drm_atomic_get_crtc_state(state, crtc);
	if (!IS_ERR(crtc_state)) {
		struct rcar_du_crtc_state *rcrtc_state;

		rcrtc_state = to_rcar_crtc_state(crtc_state);
		rcrtc_state->crc.source = source;
		rcrtc_state->crc.index = index;

		ret = drm_atomic_commit(state);
	} else {
		ret = PTR_ERR(crtc_state);
	}

	if (ret == -EDEADLK) {
		drm_atomic_state_clear(state);
		drm_modeset_backoff(&ctx);
		goto retry;
	}

	drm_atomic_state_put(state);

unlock:
	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	return 0;
}