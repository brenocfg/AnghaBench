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
struct rcar_du_encoder {int output; } ;
struct rcar_du_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  ddev; TYPE_1__* info; struct rcar_du_encoder** encoders; } ;
struct drm_panel {int dummy; } ;
struct drm_encoder {TYPE_2__* funcs; scalar_t__ name; } ;
typedef  struct drm_panel drm_bridge ;
struct device_node {int dummy; } ;
typedef  enum rcar_du_output { ____Placeholder_rcar_du_output } rcar_du_output ;
struct TYPE_4__ {int /*<<< orphan*/  (* destroy ) (struct drm_encoder*) ;} ;
struct TYPE_3__ {int gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DPI ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_NONE ; 
 int ENOLINK ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct drm_panel*) ; 
 int PTR_ERR (struct drm_panel*) ; 
 int RCAR_DU_OUTPUT_DPAD0 ; 
 int RCAR_DU_OUTPUT_DPAD1 ; 
 int RCAR_DU_OUTPUT_LVDS1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct device_node*,int) ; 
 struct drm_panel* devm_drm_panel_bridge_add (int /*<<< orphan*/ ,struct drm_panel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct rcar_du_encoder*) ; 
 struct rcar_du_encoder* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int drm_bridge_attach (struct drm_encoder*,struct drm_panel*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int drm_encoder_init (int /*<<< orphan*/ ,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encoder_funcs ; 
 int /*<<< orphan*/  encoder_helper_funcs ; 
 struct drm_panel* of_drm_find_bridge (struct device_node*) ; 
 struct drm_panel* of_drm_find_panel (struct device_node*) ; 
 int rcar_du_encoder_count_ports (struct device_node*) ; 
 struct drm_encoder* rcar_encoder_to_drm_encoder (struct rcar_du_encoder*) ; 
 scalar_t__ rcar_lvds_dual_link (struct drm_panel*) ; 
 int /*<<< orphan*/  stub1 (struct drm_encoder*) ; 

int rcar_du_encoder_init(struct rcar_du_device *rcdu,
			 enum rcar_du_output output,
			 struct device_node *enc_node)
{
	struct rcar_du_encoder *renc;
	struct drm_encoder *encoder;
	struct drm_bridge *bridge;
	int ret;

	renc = devm_kzalloc(rcdu->dev, sizeof(*renc), GFP_KERNEL);
	if (renc == NULL)
		return -ENOMEM;

	rcdu->encoders[output] = renc;
	renc->output = output;
	encoder = rcar_encoder_to_drm_encoder(renc);

	dev_dbg(rcdu->dev, "initializing encoder %pOF for output %u\n",
		enc_node, output);

	/*
	 * Locate the DRM bridge from the DT node. For the DPAD outputs, if the
	 * DT node has a single port, assume that it describes a panel and
	 * create a panel bridge.
	 */
	if ((output == RCAR_DU_OUTPUT_DPAD0 ||
	     output == RCAR_DU_OUTPUT_DPAD1) &&
	    rcar_du_encoder_count_ports(enc_node) == 1) {
		struct drm_panel *panel = of_drm_find_panel(enc_node);

		if (IS_ERR(panel)) {
			ret = PTR_ERR(panel);
			goto done;
		}

		bridge = devm_drm_panel_bridge_add(rcdu->dev, panel,
						   DRM_MODE_CONNECTOR_DPI);
		if (IS_ERR(bridge)) {
			ret = PTR_ERR(bridge);
			goto done;
		}
	} else {
		bridge = of_drm_find_bridge(enc_node);
		if (!bridge) {
			ret = -EPROBE_DEFER;
			goto done;
		}
	}

	/*
	 * On Gen3 skip the LVDS1 output if the LVDS1 encoder is used as a
	 * companion for LVDS0 in dual-link mode.
	 */
	if (rcdu->info->gen >= 3 && output == RCAR_DU_OUTPUT_LVDS1) {
		if (rcar_lvds_dual_link(bridge)) {
			ret = -ENOLINK;
			goto done;
		}
	}

	ret = drm_encoder_init(rcdu->ddev, encoder, &encoder_funcs,
			       DRM_MODE_ENCODER_NONE, NULL);
	if (ret < 0)
		goto done;

	drm_encoder_helper_add(encoder, &encoder_helper_funcs);

	/*
	 * Attach the bridge to the encoder. The bridge will create the
	 * connector.
	 */
	ret = drm_bridge_attach(encoder, bridge, NULL);
	if (ret) {
		drm_encoder_cleanup(encoder);
		return ret;
	}

done:
	if (ret < 0) {
		if (encoder->name)
			encoder->funcs->destroy(encoder);
		devm_kfree(rcdu->dev, renc);
	}

	return ret;
}