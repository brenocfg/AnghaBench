#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__** attrs; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {char* name; int /*<<< orphan*/  mode; } ;
struct TYPE_5__ {TYPE_4__ attr; int /*<<< orphan*/ * store; int /*<<< orphan*/  show; } ;
struct i915_oa_config {TYPE_3__ sysfs_metric; TYPE_4__** attrs; int /*<<< orphan*/  uuid; TYPE_1__ sysfs_metric_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  metrics_kobj; } ;
struct drm_i915_private {TYPE_2__ perf; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  show_dynamic_id ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_4__*) ; 
 int sysfs_create_group (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int create_dynamic_oa_sysfs_entry(struct drm_i915_private *dev_priv,
					 struct i915_oa_config *oa_config)
{
	sysfs_attr_init(&oa_config->sysfs_metric_id.attr);
	oa_config->sysfs_metric_id.attr.name = "id";
	oa_config->sysfs_metric_id.attr.mode = S_IRUGO;
	oa_config->sysfs_metric_id.show = show_dynamic_id;
	oa_config->sysfs_metric_id.store = NULL;

	oa_config->attrs[0] = &oa_config->sysfs_metric_id.attr;
	oa_config->attrs[1] = NULL;

	oa_config->sysfs_metric.name = oa_config->uuid;
	oa_config->sysfs_metric.attrs = oa_config->attrs;

	return sysfs_create_group(dev_priv->perf.metrics_kobj,
				  &oa_config->sysfs_metric);
}