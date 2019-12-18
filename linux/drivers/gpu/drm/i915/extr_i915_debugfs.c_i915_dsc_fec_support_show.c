#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct seq_file {struct drm_connector* private; } ;
struct intel_dp {int /*<<< orphan*/  fec_capable; int /*<<< orphan*/  force_dsc_en; int /*<<< orphan*/  dsc_dpcd; } ;
struct TYPE_7__ {int /*<<< orphan*/  compression_enable; } ;
struct intel_crtc_state {TYPE_3__ dsc_params; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  connection_mutex; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct drm_crtc {int /*<<< orphan*/  state; int /*<<< orphan*/  mutex; } ;
struct drm_connector {scalar_t__ status; TYPE_2__* state; struct drm_device* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  base; } ;
struct TYPE_6__ {struct drm_crtc* crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODESET_ACQUIRE_INTERRUPTIBLE ; 
 int EDEADLK ; 
 int ENODEV ; 
 scalar_t__ connector_status_connected ; 
 int /*<<< orphan*/  drm_dp_sink_supports_dsc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_sink_supports_fec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_acquire_fini (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_init (struct drm_modeset_acquire_ctx*,int /*<<< orphan*/ ) ; 
 int drm_modeset_backoff (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_drop_locks (struct drm_modeset_acquire_ctx*) ; 
 int drm_modeset_lock (int /*<<< orphan*/ *,struct drm_modeset_acquire_ctx*) ; 
 struct intel_dp* enc_to_intel_dp (int /*<<< orphan*/ *) ; 
 TYPE_4__* intel_attached_encoder (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 struct intel_crtc_state* to_intel_crtc_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yesno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_dsc_fec_support_show(struct seq_file *m, void *data)
{
	struct drm_connector *connector = m->private;
	struct drm_device *dev = connector->dev;
	struct drm_crtc *crtc;
	struct intel_dp *intel_dp;
	struct drm_modeset_acquire_ctx ctx;
	struct intel_crtc_state *crtc_state = NULL;
	int ret = 0;
	bool try_again = false;

	drm_modeset_acquire_init(&ctx, DRM_MODESET_ACQUIRE_INTERRUPTIBLE);

	do {
		try_again = false;
		ret = drm_modeset_lock(&dev->mode_config.connection_mutex,
				       &ctx);
		if (ret) {
			if (ret == -EDEADLK && !drm_modeset_backoff(&ctx)) {
				try_again = true;
				continue;
			}
			break;
		}
		crtc = connector->state->crtc;
		if (connector->status != connector_status_connected || !crtc) {
			ret = -ENODEV;
			break;
		}
		ret = drm_modeset_lock(&crtc->mutex, &ctx);
		if (ret == -EDEADLK) {
			ret = drm_modeset_backoff(&ctx);
			if (!ret) {
				try_again = true;
				continue;
			}
			break;
		} else if (ret) {
			break;
		}
		intel_dp = enc_to_intel_dp(&intel_attached_encoder(connector)->base);
		crtc_state = to_intel_crtc_state(crtc->state);
		seq_printf(m, "DSC_Enabled: %s\n",
			   yesno(crtc_state->dsc_params.compression_enable));
		seq_printf(m, "DSC_Sink_Support: %s\n",
			   yesno(drm_dp_sink_supports_dsc(intel_dp->dsc_dpcd)));
		seq_printf(m, "Force_DSC_Enable: %s\n",
			   yesno(intel_dp->force_dsc_en));
		if (!intel_dp_is_edp(intel_dp))
			seq_printf(m, "FEC_Sink_Support: %s\n",
				   yesno(drm_dp_sink_supports_fec(intel_dp->fec_capable)));
	} while (try_again);

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	return ret;
}