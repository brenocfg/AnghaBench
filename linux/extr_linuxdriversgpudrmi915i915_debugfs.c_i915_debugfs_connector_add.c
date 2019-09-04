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
struct drm_connector {scalar_t__ connector_type; struct dentry* debugfs_entry; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ DRM_MODE_CONNECTOR_DisplayPort ; 
 scalar_t__ DRM_MODE_CONNECTOR_eDP ; 
 int ENODEV ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int /*<<< orphan*/ ,struct dentry*,struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_dpcd_fops ; 
 int /*<<< orphan*/  i915_panel_fops ; 
 int /*<<< orphan*/  i915_psr_sink_status_fops ; 

int i915_debugfs_connector_add(struct drm_connector *connector)
{
	struct dentry *root = connector->debugfs_entry;

	/* The connector must have been registered beforehands. */
	if (!root)
		return -ENODEV;

	if (connector->connector_type == DRM_MODE_CONNECTOR_DisplayPort ||
	    connector->connector_type == DRM_MODE_CONNECTOR_eDP)
		debugfs_create_file("i915_dpcd", S_IRUGO, root,
				    connector, &i915_dpcd_fops);

	if (connector->connector_type == DRM_MODE_CONNECTOR_eDP) {
		debugfs_create_file("i915_panel_timings", S_IRUGO, root,
				    connector, &i915_panel_fops);
		debugfs_create_file("i915_psr_sink_status", S_IRUGO, root,
				    connector, &i915_psr_sink_status_fops);
	}

	return 0;
}