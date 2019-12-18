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
struct edid {int dummy; } ;
struct drm_connector {TYPE_1__* edid_blob_ptr; scalar_t__ override_edid; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct edid*) ; 
 struct edid* drm_edid_duplicate (int /*<<< orphan*/ ) ; 
 struct edid* drm_load_edid_firmware (struct drm_connector*) ; 

__attribute__((used)) static struct edid *drm_get_override_edid(struct drm_connector *connector)
{
	struct edid *override = NULL;

	if (connector->override_edid)
		override = drm_edid_duplicate(connector->edid_blob_ptr->data);

	if (!override)
		override = drm_load_edid_firmware(connector);

	return IS_ERR(override) ? NULL : override;
}