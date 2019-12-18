#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omap_drm_private {unsigned int num_pipes; int /*<<< orphan*/  channels; struct omap_drm_pipeline* pipes; } ;
struct omap_drm_pipeline {TYPE_1__* output; } ;
struct drm_device {struct omap_drm_private* dev_private; } ;
struct TYPE_3__ {scalar_t__ panel; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_panel_detach (scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omapdss_device_disconnect (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  omapdss_device_put (TYPE_1__*) ; 

__attribute__((used)) static void omap_disconnect_pipelines(struct drm_device *ddev)
{
	struct omap_drm_private *priv = ddev->dev_private;
	unsigned int i;

	for (i = 0; i < priv->num_pipes; i++) {
		struct omap_drm_pipeline *pipe = &priv->pipes[i];

		if (pipe->output->panel)
			drm_panel_detach(pipe->output->panel);

		omapdss_device_disconnect(NULL, pipe->output);

		omapdss_device_put(pipe->output);
		pipe->output = NULL;
	}

	memset(&priv->channels, 0, sizeof(priv->channels));

	priv->num_pipes = 0;
}