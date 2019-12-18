#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct seq_file {struct drm_info_node* private; } ;
struct drm_info_node {TYPE_1__* info_ent; } ;
struct TYPE_10__ {TYPE_2__* vma; } ;
struct TYPE_11__ {TYPE_3__ log; } ;
struct TYPE_12__ {TYPE_4__ guc; struct drm_i915_gem_object* load_err_log; } ;
struct TYPE_13__ {TYPE_5__ uc; } ;
struct drm_i915_private {TYPE_6__ gt; } ;
struct TYPE_14__ {int size; } ;
struct drm_i915_gem_object {TYPE_7__ base; } ;
struct TYPE_9__ {struct drm_i915_gem_object* obj; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  HAS_GT_UC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_MAP_WC ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * i915_gem_object_pin_map (struct drm_i915_gem_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_map (struct drm_i915_gem_object*) ; 
 struct drm_i915_private* node_to_i915 (struct drm_info_node*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int i915_guc_log_dump(struct seq_file *m, void *data)
{
	struct drm_info_node *node = m->private;
	struct drm_i915_private *dev_priv = node_to_i915(node);
	bool dump_load_err = !!node->info_ent->data;
	struct drm_i915_gem_object *obj = NULL;
	u32 *log;
	int i = 0;

	if (!HAS_GT_UC(dev_priv))
		return -ENODEV;

	if (dump_load_err)
		obj = dev_priv->gt.uc.load_err_log;
	else if (dev_priv->gt.uc.guc.log.vma)
		obj = dev_priv->gt.uc.guc.log.vma->obj;

	if (!obj)
		return 0;

	log = i915_gem_object_pin_map(obj, I915_MAP_WC);
	if (IS_ERR(log)) {
		DRM_DEBUG("Failed to pin object\n");
		seq_puts(m, "(log data unaccessible)\n");
		return PTR_ERR(log);
	}

	for (i = 0; i < obj->base.size / sizeof(u32); i += 4)
		seq_printf(m, "0x%08x 0x%08x 0x%08x 0x%08x\n",
			   *(log + i), *(log + i + 1),
			   *(log + i + 2), *(log + i + 3));

	seq_putc(m, '\n');

	i915_gem_object_unpin_map(obj);

	return 0;
}