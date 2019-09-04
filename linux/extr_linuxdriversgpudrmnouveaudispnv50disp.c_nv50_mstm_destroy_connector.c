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
struct nv50_mstc {int /*<<< orphan*/  connector; int /*<<< orphan*/ * port; } ;
struct nouveau_drm {TYPE_3__* dev; TYPE_1__* fbcon; } ;
struct drm_dp_mst_topology_mgr {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  connection_mutex; } ;
struct TYPE_6__ {TYPE_2__ mode_config; } ;
struct TYPE_4__ {int /*<<< orphan*/  helper; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_helper_remove_one_connector (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_unlock (int /*<<< orphan*/ *) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 
 struct nv50_mstc* nv50_mstc (struct drm_connector*) ; 

__attribute__((used)) static void
nv50_mstm_destroy_connector(struct drm_dp_mst_topology_mgr *mgr,
			    struct drm_connector *connector)
{
	struct nouveau_drm *drm = nouveau_drm(connector->dev);
	struct nv50_mstc *mstc = nv50_mstc(connector);

	drm_connector_unregister(&mstc->connector);

	drm_fb_helper_remove_one_connector(&drm->fbcon->helper, &mstc->connector);

	drm_modeset_lock(&drm->dev->mode_config.connection_mutex, NULL);
	mstc->port = NULL;
	drm_modeset_unlock(&drm->dev->mode_config.connection_mutex);

	drm_connector_put(&mstc->connector);
}