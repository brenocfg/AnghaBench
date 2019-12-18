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
struct dumb_vga {scalar_t__ ddc; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int connector_status_connected ; 
 int connector_status_unknown ; 
 struct dumb_vga* drm_connector_to_dumb_vga (struct drm_connector*) ; 
 scalar_t__ drm_probe_ddc (scalar_t__) ; 

__attribute__((used)) static enum drm_connector_status
dumb_vga_connector_detect(struct drm_connector *connector, bool force)
{
	struct dumb_vga *vga = drm_connector_to_dumb_vga(connector);

	/*
	 * Even if we have an I2C bus, we can't assume that the cable
	 * is disconnected if drm_probe_ddc fails. Some cables don't
	 * wire the DDC pins, or the I2C bus might not be working at
	 * all.
	 */
	if (vga->ddc && drm_probe_ddc(vga->ddc))
		return connector_status_connected;

	return connector_status_unknown;
}