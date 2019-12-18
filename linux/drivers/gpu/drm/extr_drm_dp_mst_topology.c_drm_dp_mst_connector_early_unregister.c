#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct drm_dp_mst_port {TYPE_3__ aux; } ;
struct drm_connector {TYPE_2__* kdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_1__ kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_aux_unregister_devnode (TYPE_3__*) ; 

void drm_dp_mst_connector_early_unregister(struct drm_connector *connector,
					   struct drm_dp_mst_port *port)
{
	DRM_DEBUG_KMS("unregistering %s remote bus for %s\n",
		      port->aux.name, connector->kdev->kobj.name);
	drm_dp_aux_unregister_devnode(&port->aux);
}