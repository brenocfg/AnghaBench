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
struct TYPE_2__ {scalar_t__ disconnected; } ;
struct vbox_connector {TYPE_1__ mode_hint; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 struct vbox_connector* to_vbox_connector (struct drm_connector*) ; 

__attribute__((used)) static enum drm_connector_status
vbox_connector_detect(struct drm_connector *connector, bool force)
{
	struct vbox_connector *vbox_connector;

	vbox_connector = to_vbox_connector(connector);

	return vbox_connector->mode_hint.disconnected ?
	    connector_status_disconnected : connector_status_connected;
}