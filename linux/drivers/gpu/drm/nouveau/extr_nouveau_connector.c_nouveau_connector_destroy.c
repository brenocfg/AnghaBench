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
struct TYPE_3__ {struct drm_connector* name; scalar_t__ transfer; } ;
struct nouveau_connector {TYPE_1__ aux; struct drm_connector* edid; int /*<<< orphan*/  hpd; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_unregister (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_dp_aux_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_dp_cec_unregister_connector (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct drm_connector*) ; 
 struct nouveau_connector* nouveau_connector (struct drm_connector*) ; 
 int /*<<< orphan*/  nvif_notify_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nouveau_connector_destroy(struct drm_connector *connector)
{
	struct nouveau_connector *nv_connector = nouveau_connector(connector);
	nvif_notify_fini(&nv_connector->hpd);
	kfree(nv_connector->edid);
	drm_connector_unregister(connector);
	drm_connector_cleanup(connector);
	if (nv_connector->aux.transfer) {
		drm_dp_cec_unregister_connector(&nv_connector->aux);
		drm_dp_aux_unregister(&nv_connector->aux);
		kfree(nv_connector->aux.name);
	}
	kfree(connector);
}