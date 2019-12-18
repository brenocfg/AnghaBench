#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dentry {int dummy; } ;
struct TYPE_4__ {scalar_t__ connector_type; struct dentry* debugfs_entry; } ;
struct amdgpu_dm_connector {TYPE_1__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  fops; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 scalar_t__ DRM_MODE_CONNECTOR_DisplayPort ; 
 scalar_t__ DRM_MODE_CONNECTOR_eDP ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int,struct dentry*,struct amdgpu_dm_connector*,int /*<<< orphan*/ ) ; 
 TYPE_2__* dp_debugfs_entries ; 

void connector_debugfs_init(struct amdgpu_dm_connector *connector)
{
	int i;
	struct dentry *dir = connector->base.debugfs_entry;

	if (connector->base.connector_type == DRM_MODE_CONNECTOR_DisplayPort ||
	    connector->base.connector_type == DRM_MODE_CONNECTOR_eDP) {
		for (i = 0; i < ARRAY_SIZE(dp_debugfs_entries); i++) {
			debugfs_create_file(dp_debugfs_entries[i].name,
					    0644, dir, connector,
					    dp_debugfs_entries[i].fops);
		}
	}
}