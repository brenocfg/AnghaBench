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
struct tilcdc_drm_private {int /*<<< orphan*/  crtc; } ;
struct drm_display_mode {int dummy; } ;
struct drm_connector {TYPE_1__* dev; } ;
struct TYPE_2__ {struct tilcdc_drm_private* dev_private; } ;

/* Variables and functions */
 int tilcdc_crtc_mode_valid (int /*<<< orphan*/ ,struct drm_display_mode*) ; 

__attribute__((used)) static int tfp410_connector_mode_valid(struct drm_connector *connector,
		  struct drm_display_mode *mode)
{
	struct tilcdc_drm_private *priv = connector->dev->dev_private;
	/* our only constraints are what the crtc can generate: */
	return tilcdc_crtc_mode_valid(priv->crtc, mode);
}