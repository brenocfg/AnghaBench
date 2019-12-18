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
struct intel_vgpu {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  mmio_context_lock; } ;
struct intel_gvt {int /*<<< orphan*/  vgpu_idr; struct intel_vgpu* idle_vgpu; struct drm_i915_private* dev_priv; int /*<<< orphan*/  sched_lock; int /*<<< orphan*/  lock; TYPE_1__ scheduler; } ;
struct TYPE_7__ {TYPE_2__* pdev; } ;
struct drm_i915_private {TYPE_3__ drm; struct intel_gvt* gvt; } ;
struct TYPE_8__ {int initialized; int /*<<< orphan*/ * dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct intel_vgpu*) ; 
 int PTR_ERR (struct intel_vgpu*) ; 
 scalar_t__ WARN_ON (struct intel_gvt*) ; 
 int /*<<< orphan*/  clean_service_thread (struct intel_gvt*) ; 
 int /*<<< orphan*/  gvt_dbg_core (char*) ; 
 int /*<<< orphan*/  gvt_err (char*,...) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_device_info (struct intel_gvt*) ; 
 int init_service_thread (struct intel_gvt*) ; 
 int /*<<< orphan*/  intel_gvt_clean_cmd_parser (struct intel_gvt*) ; 
 int /*<<< orphan*/  intel_gvt_clean_gtt (struct intel_gvt*) ; 
 int /*<<< orphan*/  intel_gvt_clean_irq (struct intel_gvt*) ; 
 int /*<<< orphan*/  intel_gvt_clean_mmio_info (struct intel_gvt*) ; 
 int /*<<< orphan*/  intel_gvt_clean_sched_policy (struct intel_gvt*) ; 
 int /*<<< orphan*/  intel_gvt_clean_vgpu_types (struct intel_gvt*) ; 
 int /*<<< orphan*/  intel_gvt_clean_workload_scheduler (struct intel_gvt*) ; 
 struct intel_vgpu* intel_gvt_create_idle_vgpu (struct intel_gvt*) ; 
 int /*<<< orphan*/  intel_gvt_debugfs_init (struct intel_gvt*) ; 
 int /*<<< orphan*/  intel_gvt_free_firmware (struct intel_gvt*) ; 
 TYPE_4__ intel_gvt_host ; 
 int intel_gvt_init_cmd_parser (struct intel_gvt*) ; 
 int /*<<< orphan*/  intel_gvt_init_engine_mmio_context (struct intel_gvt*) ; 
 int intel_gvt_init_gtt (struct intel_gvt*) ; 
 int intel_gvt_init_irq (struct intel_gvt*) ; 
 int intel_gvt_init_sched_policy (struct intel_gvt*) ; 
 int intel_gvt_init_vgpu_type_groups (struct intel_gvt*) ; 
 int intel_gvt_init_vgpu_types (struct intel_gvt*) ; 
 int intel_gvt_init_workload_scheduler (struct intel_gvt*) ; 
 int intel_gvt_load_firmware (struct intel_gvt*) ; 
 int intel_gvt_setup_mmio_info (struct intel_gvt*) ; 
 int /*<<< orphan*/  kfree (struct intel_gvt*) ; 
 struct intel_gvt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int intel_gvt_init_device(struct drm_i915_private *dev_priv)
{
	struct intel_gvt *gvt;
	struct intel_vgpu *vgpu;
	int ret;

	if (WARN_ON(dev_priv->gvt))
		return -EEXIST;

	gvt = kzalloc(sizeof(struct intel_gvt), GFP_KERNEL);
	if (!gvt)
		return -ENOMEM;

	gvt_dbg_core("init gvt device\n");

	idr_init(&gvt->vgpu_idr);
	spin_lock_init(&gvt->scheduler.mmio_context_lock);
	mutex_init(&gvt->lock);
	mutex_init(&gvt->sched_lock);
	gvt->dev_priv = dev_priv;

	init_device_info(gvt);

	ret = intel_gvt_setup_mmio_info(gvt);
	if (ret)
		goto out_clean_idr;

	intel_gvt_init_engine_mmio_context(gvt);

	ret = intel_gvt_load_firmware(gvt);
	if (ret)
		goto out_clean_mmio_info;

	ret = intel_gvt_init_irq(gvt);
	if (ret)
		goto out_free_firmware;

	ret = intel_gvt_init_gtt(gvt);
	if (ret)
		goto out_clean_irq;

	ret = intel_gvt_init_workload_scheduler(gvt);
	if (ret)
		goto out_clean_gtt;

	ret = intel_gvt_init_sched_policy(gvt);
	if (ret)
		goto out_clean_workload_scheduler;

	ret = intel_gvt_init_cmd_parser(gvt);
	if (ret)
		goto out_clean_sched_policy;

	ret = init_service_thread(gvt);
	if (ret)
		goto out_clean_cmd_parser;

	ret = intel_gvt_init_vgpu_types(gvt);
	if (ret)
		goto out_clean_thread;

	ret = intel_gvt_init_vgpu_type_groups(gvt);
	if (ret == false) {
		gvt_err("failed to init vgpu type groups: %d\n", ret);
		goto out_clean_types;
	}

	vgpu = intel_gvt_create_idle_vgpu(gvt);
	if (IS_ERR(vgpu)) {
		ret = PTR_ERR(vgpu);
		gvt_err("failed to create idle vgpu\n");
		goto out_clean_types;
	}
	gvt->idle_vgpu = vgpu;

	intel_gvt_debugfs_init(gvt);

	gvt_dbg_core("gvt device initialization is done\n");
	dev_priv->gvt = gvt;
	intel_gvt_host.dev = &dev_priv->drm.pdev->dev;
	intel_gvt_host.initialized = true;
	return 0;

out_clean_types:
	intel_gvt_clean_vgpu_types(gvt);
out_clean_thread:
	clean_service_thread(gvt);
out_clean_cmd_parser:
	intel_gvt_clean_cmd_parser(gvt);
out_clean_sched_policy:
	intel_gvt_clean_sched_policy(gvt);
out_clean_workload_scheduler:
	intel_gvt_clean_workload_scheduler(gvt);
out_clean_gtt:
	intel_gvt_clean_gtt(gvt);
out_clean_irq:
	intel_gvt_clean_irq(gvt);
out_free_firmware:
	intel_gvt_free_firmware(gvt);
out_clean_mmio_info:
	intel_gvt_clean_mmio_info(gvt);
out_clean_idr:
	idr_destroy(&gvt->vgpu_idr);
	kfree(gvt);
	return ret;
}