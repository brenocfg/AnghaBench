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
struct edid {int dummy; } ;
struct drm_psb_private {size_t crt_ddc_pin; TYPE_2__* gmbus; } ;
struct drm_connector {TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  adapter; } ;
struct TYPE_3__ {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct edid *
psb_intel_sdvo_get_analog_edid(struct drm_connector *connector)
{
	struct drm_psb_private *dev_priv = connector->dev->dev_private;

	return drm_get_edid(connector,
			    &dev_priv->gmbus[dev_priv->crt_ddc_pin].adapter);
}