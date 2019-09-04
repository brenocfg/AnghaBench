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
typedef  int /*<<< orphan*/  u8 ;
struct ptn3460_bridge {int /*<<< orphan*/  bridge; struct edid* edid; int /*<<< orphan*/  enabled; } ;
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  EDID_LENGTH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PTN3460_EDID_ADDR ; 
 struct ptn3460_bridge* connector_to_ptn3460 (struct drm_connector*) ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptn3460_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptn3460_pre_enable (int /*<<< orphan*/ *) ; 
 int ptn3460_read_bytes (struct ptn3460_bridge*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ptn3460_get_modes(struct drm_connector *connector)
{
	struct ptn3460_bridge *ptn_bridge;
	u8 *edid;
	int ret, num_modes = 0;
	bool power_off;

	ptn_bridge = connector_to_ptn3460(connector);

	if (ptn_bridge->edid)
		return drm_add_edid_modes(connector, ptn_bridge->edid);

	power_off = !ptn_bridge->enabled;
	ptn3460_pre_enable(&ptn_bridge->bridge);

	edid = kmalloc(EDID_LENGTH, GFP_KERNEL);
	if (!edid) {
		DRM_ERROR("Failed to allocate EDID\n");
		return 0;
	}

	ret = ptn3460_read_bytes(ptn_bridge, PTN3460_EDID_ADDR, edid,
			EDID_LENGTH);
	if (ret) {
		kfree(edid);
		goto out;
	}

	ptn_bridge->edid = (struct edid *)edid;
	drm_connector_update_edid_property(connector, ptn_bridge->edid);

	num_modes = drm_add_edid_modes(connector, ptn_bridge->edid);

out:
	if (power_off)
		ptn3460_disable(&ptn_bridge->bridge);

	return num_modes;
}