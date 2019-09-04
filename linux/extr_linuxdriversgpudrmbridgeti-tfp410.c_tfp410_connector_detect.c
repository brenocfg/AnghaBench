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
struct tfp410 {scalar_t__ ddc; scalar_t__ hpd; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int connector_status_unknown ; 
 struct tfp410* drm_connector_to_tfp410 (struct drm_connector*) ; 
 scalar_t__ drm_probe_ddc (scalar_t__) ; 
 scalar_t__ gpiod_get_value_cansleep (scalar_t__) ; 

__attribute__((used)) static enum drm_connector_status
tfp410_connector_detect(struct drm_connector *connector, bool force)
{
	struct tfp410 *dvi = drm_connector_to_tfp410(connector);

	if (dvi->hpd) {
		if (gpiod_get_value_cansleep(dvi->hpd))
			return connector_status_connected;
		else
			return connector_status_disconnected;
	}

	if (dvi->ddc) {
		if (drm_probe_ddc(dvi->ddc))
			return connector_status_connected;
		else
			return connector_status_disconnected;
	}

	return connector_status_unknown;
}