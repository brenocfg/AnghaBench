#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_7__ base; } ;
struct intel_dp {struct intel_connector* attached_connector; } ;
struct TYPE_12__ {int /*<<< orphan*/  active; } ;
struct intel_crtc_state {scalar_t__ has_pch_encoder; TYPE_5__ base; } ;
struct TYPE_11__ {int /*<<< orphan*/  state; int /*<<< orphan*/  mutex; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; TYPE_4__ base; } ;
struct TYPE_10__ {scalar_t__ status; struct drm_connector_state* state; } ;
struct intel_connector {TYPE_3__ base; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  connection_mutex; } ;
struct TYPE_9__ {TYPE_1__ mode_config; } ;
struct drm_i915_private {TYPE_2__ drm; } ;
struct drm_connector_state {TYPE_6__* commit; int /*<<< orphan*/  crtc; } ;
struct TYPE_13__ {int /*<<< orphan*/  hw_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ connector_status_connected ; 
 int drm_modeset_lock (int /*<<< orphan*/ *,struct drm_modeset_acquire_ctx*) ; 
 struct intel_dp* enc_to_intel_dp (TYPE_7__*) ; 
 int /*<<< orphan*/  intel_crtc_has_dp_encoder (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_crtc_pch_transcoder (struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_dp_needs_link_retrain (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_start_link_train (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_stop_link_train (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_set_cpu_fifo_underrun_reporting (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_set_pch_fifo_underrun_reporting (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_wait_for_vblank (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 struct intel_crtc_state* to_intel_crtc_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_wait_for_completion (int /*<<< orphan*/ *) ; 

int intel_dp_retrain_link(struct intel_encoder *encoder,
			  struct drm_modeset_acquire_ctx *ctx)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);
	struct intel_connector *connector = intel_dp->attached_connector;
	struct drm_connector_state *conn_state;
	struct intel_crtc_state *crtc_state;
	struct intel_crtc *crtc;
	int ret;

	/* FIXME handle the MST connectors as well */

	if (!connector || connector->base.status != connector_status_connected)
		return 0;

	ret = drm_modeset_lock(&dev_priv->drm.mode_config.connection_mutex,
			       ctx);
	if (ret)
		return ret;

	conn_state = connector->base.state;

	crtc = to_intel_crtc(conn_state->crtc);
	if (!crtc)
		return 0;

	ret = drm_modeset_lock(&crtc->base.mutex, ctx);
	if (ret)
		return ret;

	crtc_state = to_intel_crtc_state(crtc->base.state);

	WARN_ON(!intel_crtc_has_dp_encoder(crtc_state));

	if (!crtc_state->base.active)
		return 0;

	if (conn_state->commit &&
	    !try_wait_for_completion(&conn_state->commit->hw_done))
		return 0;

	if (!intel_dp_needs_link_retrain(intel_dp))
		return 0;

	/* Suppress underruns caused by re-training */
	intel_set_cpu_fifo_underrun_reporting(dev_priv, crtc->pipe, false);
	if (crtc_state->has_pch_encoder)
		intel_set_pch_fifo_underrun_reporting(dev_priv,
						      intel_crtc_pch_transcoder(crtc), false);

	intel_dp_start_link_train(intel_dp);
	intel_dp_stop_link_train(intel_dp);

	/* Keep underrun reporting disabled until things are stable */
	intel_wait_for_vblank(dev_priv, crtc->pipe);

	intel_set_cpu_fifo_underrun_reporting(dev_priv, crtc->pipe, true);
	if (crtc_state->has_pch_encoder)
		intel_set_pch_fifo_underrun_reporting(dev_priv,
						      intel_crtc_pch_transcoder(crtc), true);

	return 0;
}