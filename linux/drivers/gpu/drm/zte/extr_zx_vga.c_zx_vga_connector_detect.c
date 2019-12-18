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
struct zx_vga {scalar_t__ connected; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 struct zx_vga* to_zx_vga (struct drm_connector*) ; 

__attribute__((used)) static enum drm_connector_status
zx_vga_connector_detect(struct drm_connector *connector, bool force)
{
	struct zx_vga *vga = to_zx_vga(connector);

	return vga->connected ? connector_status_connected :
				connector_status_disconnected;
}