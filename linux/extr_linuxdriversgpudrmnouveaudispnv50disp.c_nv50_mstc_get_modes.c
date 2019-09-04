#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int bpc; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; TYPE_1__ display_info; } ;
struct nv50_mstc {TYPE_2__ connector; scalar_t__ native; scalar_t__ edid; TYPE_4__* port; } ;
struct drm_connector {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  mgr; } ;

/* Variables and functions */
 int drm_add_edid_modes (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (TYPE_2__*,scalar_t__) ; 
 scalar_t__ drm_dp_mst_get_edid (TYPE_2__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  drm_mode_destroy (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nouveau_conn_native_mode (TYPE_2__*) ; 
 struct nv50_mstc* nv50_mstc (struct drm_connector*) ; 

__attribute__((used)) static int
nv50_mstc_get_modes(struct drm_connector *connector)
{
	struct nv50_mstc *mstc = nv50_mstc(connector);
	int ret = 0;

	mstc->edid = drm_dp_mst_get_edid(&mstc->connector, mstc->port->mgr, mstc->port);
	drm_connector_update_edid_property(&mstc->connector, mstc->edid);
	if (mstc->edid)
		ret = drm_add_edid_modes(&mstc->connector, mstc->edid);

	if (!mstc->connector.display_info.bpc)
		mstc->connector.display_info.bpc = 8;

	if (mstc->native)
		drm_mode_destroy(mstc->connector.dev, mstc->native);
	mstc->native = nouveau_conn_native_mode(&mstc->connector);
	return ret;
}