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
struct tilcdc_drm_private {int /*<<< orphan*/  wq; } ;
struct drm_crtc {int /*<<< orphan*/  port; TYPE_1__* dev; } ;
struct TYPE_2__ {struct tilcdc_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_cleanup (struct drm_crtc*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tilcdc_crtc_shutdown (struct drm_crtc*) ; 

__attribute__((used)) static void tilcdc_crtc_destroy(struct drm_crtc *crtc)
{
	struct tilcdc_drm_private *priv = crtc->dev->dev_private;

	tilcdc_crtc_shutdown(crtc);

	flush_workqueue(priv->wq);

	of_node_put(crtc->port);
	drm_crtc_cleanup(crtc);
}