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
struct intel_encoder {int crtc_mask; int /*<<< orphan*/  get_config; int /*<<< orphan*/  get_hw_state; int /*<<< orphan*/  enable; int /*<<< orphan*/  pre_enable; int /*<<< orphan*/  post_pll_disable; int /*<<< orphan*/  pre_pll_enable; int /*<<< orphan*/  post_disable; int /*<<< orphan*/  disable; int /*<<< orphan*/  compute_config; scalar_t__ cloneable; int /*<<< orphan*/  port; int /*<<< orphan*/  power_domain; int /*<<< orphan*/  type; int /*<<< orphan*/  base; } ;
struct intel_dp_mst_encoder {int pipe; struct intel_digital_port* primary; struct intel_encoder base; } ;
struct TYPE_3__ {struct drm_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; int /*<<< orphan*/  power_domain; TYPE_1__ base; } ;
struct intel_digital_port {TYPE_2__ base; } ;
struct drm_device {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ENCODER_DPMST ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INTEL_OUTPUT_DP_MST ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_mst_compute_config ; 
 int /*<<< orphan*/  intel_dp_mst_enc_funcs ; 
 int /*<<< orphan*/  intel_dp_mst_enc_get_config ; 
 int /*<<< orphan*/  intel_dp_mst_enc_get_hw_state ; 
 int /*<<< orphan*/  intel_mst_disable_dp ; 
 int /*<<< orphan*/  intel_mst_enable_dp ; 
 int /*<<< orphan*/  intel_mst_post_disable_dp ; 
 int /*<<< orphan*/  intel_mst_post_pll_disable_dp ; 
 int /*<<< orphan*/  intel_mst_pre_enable_dp ; 
 int /*<<< orphan*/  intel_mst_pre_pll_enable_dp ; 
 struct intel_dp_mst_encoder* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_name (int) ; 

__attribute__((used)) static struct intel_dp_mst_encoder *
intel_dp_create_fake_mst_encoder(struct intel_digital_port *intel_dig_port, enum pipe pipe)
{
	struct intel_dp_mst_encoder *intel_mst;
	struct intel_encoder *intel_encoder;
	struct drm_device *dev = intel_dig_port->base.base.dev;

	intel_mst = kzalloc(sizeof(*intel_mst), GFP_KERNEL);

	if (!intel_mst)
		return NULL;

	intel_mst->pipe = pipe;
	intel_encoder = &intel_mst->base;
	intel_mst->primary = intel_dig_port;

	drm_encoder_init(dev, &intel_encoder->base, &intel_dp_mst_enc_funcs,
			 DRM_MODE_ENCODER_DPMST, "DP-MST %c", pipe_name(pipe));

	intel_encoder->type = INTEL_OUTPUT_DP_MST;
	intel_encoder->power_domain = intel_dig_port->base.power_domain;
	intel_encoder->port = intel_dig_port->base.port;
	intel_encoder->crtc_mask = 0x7;
	intel_encoder->cloneable = 0;

	intel_encoder->compute_config = intel_dp_mst_compute_config;
	intel_encoder->disable = intel_mst_disable_dp;
	intel_encoder->post_disable = intel_mst_post_disable_dp;
	intel_encoder->pre_pll_enable = intel_mst_pre_pll_enable_dp;
	intel_encoder->post_pll_disable = intel_mst_post_pll_disable_dp;
	intel_encoder->pre_enable = intel_mst_pre_enable_dp;
	intel_encoder->enable = intel_mst_enable_dp;
	intel_encoder->get_hw_state = intel_dp_mst_enc_get_hw_state;
	intel_encoder->get_config = intel_dp_mst_enc_get_config;

	return intel_mst;

}