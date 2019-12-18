#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {struct drm_connector* private; } ;
struct TYPE_3__ {int /*<<< orphan*/  shim; } ;
struct intel_connector {TYPE_1__ hdcp; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct drm_connector {scalar_t__ status; TYPE_2__ base; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ connector_status_connected ; 
 int /*<<< orphan*/  intel_hdcp_info (struct seq_file*,struct intel_connector*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct intel_connector* to_intel_connector (struct drm_connector*) ; 

__attribute__((used)) static int i915_hdcp_sink_capability_show(struct seq_file *m, void *data)
{
	struct drm_connector *connector = m->private;
	struct intel_connector *intel_connector = to_intel_connector(connector);

	if (connector->status != connector_status_connected)
		return -ENODEV;

	/* HDCP is supported by connector */
	if (!intel_connector->hdcp.shim)
		return -EINVAL;

	seq_printf(m, "%s:%d HDCP version: ", connector->name,
		   connector->base.id);
	intel_hdcp_info(m, intel_connector);

	return 0;
}