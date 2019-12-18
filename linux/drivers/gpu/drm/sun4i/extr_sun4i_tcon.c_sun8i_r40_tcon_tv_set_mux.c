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
struct sun4i_tcon {int /*<<< orphan*/  id; TYPE_1__* dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct drm_encoder {scalar_t__ encoder_type; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DRM_SUN8I_TCON_TOP ; 
 scalar_t__ DRM_MODE_ENCODER_TMDS ; 
 int EINVAL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 struct device_node* of_graph_get_port_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device_node* of_graph_get_remote_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int sun4i_tcon_of_get_id_from_port (struct device_node*) ; 
 int sun8i_tcon_top_de_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int sun8i_tcon_top_set_hdmi_src (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sun8i_r40_tcon_tv_set_mux(struct sun4i_tcon *tcon,
				     const struct drm_encoder *encoder)
{
	struct device_node *port, *remote;
	struct platform_device *pdev;
	int id, ret;

	/* find TCON TOP platform device and TCON id */

	port = of_graph_get_port_by_id(tcon->dev->of_node, 0);
	if (!port)
		return -EINVAL;

	id = sun4i_tcon_of_get_id_from_port(port);
	of_node_put(port);

	remote = of_graph_get_remote_node(tcon->dev->of_node, 0, -1);
	if (!remote)
		return -EINVAL;

	pdev = of_find_device_by_node(remote);
	of_node_put(remote);
	if (!pdev)
		return -EINVAL;

	if (IS_ENABLED(CONFIG_DRM_SUN8I_TCON_TOP) &&
	    encoder->encoder_type == DRM_MODE_ENCODER_TMDS) {
		ret = sun8i_tcon_top_set_hdmi_src(&pdev->dev, id);
		if (ret)
			return ret;
	}

	if (IS_ENABLED(CONFIG_DRM_SUN8I_TCON_TOP)) {
		ret = sun8i_tcon_top_de_config(&pdev->dev, tcon->id, id);
		if (ret)
			return ret;
	}

	return 0;
}