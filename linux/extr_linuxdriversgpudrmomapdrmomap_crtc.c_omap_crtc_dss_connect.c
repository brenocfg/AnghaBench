#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct omap_dss_device {int id; int dispc_channel_connected; } ;
struct omap_drm_private {struct dispc_device* dispc; struct dispc_ops* dispc_ops; } ;
struct dispc_ops {int (* mgr_get_supported_outputs ) (struct dispc_device*,int) ;} ;
struct dispc_device {int dummy; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int EINVAL ; 
 struct omap_dss_device** omap_crtc_output ; 
 int stub1 (struct dispc_device*,int) ; 

__attribute__((used)) static int omap_crtc_dss_connect(struct omap_drm_private *priv,
		enum omap_channel channel,
		struct omap_dss_device *dst)
{
	const struct dispc_ops *dispc_ops = priv->dispc_ops;
	struct dispc_device *dispc = priv->dispc;

	if (omap_crtc_output[channel])
		return -EINVAL;

	if (!(dispc_ops->mgr_get_supported_outputs(dispc, channel) & dst->id))
		return -EINVAL;

	omap_crtc_output[channel] = dst;
	dst->dispc_channel_connected = true;

	return 0;
}