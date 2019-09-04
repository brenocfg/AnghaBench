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
struct rcar_du_encoder {int output; } ;
struct rcar_du_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  ddev; } ;
struct drm_encoder {TYPE_1__* funcs; scalar_t__ name; } ;
struct drm_bridge {int dummy; } ;
struct device_node {int dummy; } ;
typedef  enum rcar_du_output { ____Placeholder_rcar_du_output } rcar_du_output ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (struct drm_encoder*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ENCODER_NONE ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct device_node*,int) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct rcar_du_encoder*) ; 
 struct rcar_du_encoder* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int drm_bridge_attach (struct drm_encoder*,struct drm_bridge*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int drm_encoder_init (int /*<<< orphan*/ ,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encoder_funcs ; 
 int /*<<< orphan*/  encoder_helper_funcs ; 
 struct drm_bridge* of_drm_find_bridge (struct device_node*) ; 
 struct drm_encoder* rcar_encoder_to_drm_encoder (struct rcar_du_encoder*) ; 
 int /*<<< orphan*/  stub1 (struct drm_encoder*) ; 

int rcar_du_encoder_init(struct rcar_du_device *rcdu,
			 enum rcar_du_output output,
			 struct device_node *enc_node,
			 struct device_node *con_node)
{
	struct rcar_du_encoder *renc;
	struct drm_encoder *encoder;
	struct drm_bridge *bridge = NULL;
	int ret;

	renc = devm_kzalloc(rcdu->dev, sizeof(*renc), GFP_KERNEL);
	if (renc == NULL)
		return -ENOMEM;

	renc->output = output;
	encoder = rcar_encoder_to_drm_encoder(renc);

	dev_dbg(rcdu->dev, "initializing encoder %pOF for output %u\n",
		enc_node, output);

	/* Locate the DRM bridge from the encoder DT node. */
	bridge = of_drm_find_bridge(enc_node);
	if (!bridge) {
		ret = -EPROBE_DEFER;
		goto done;
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