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
struct seq_file {struct drm_info_node* private; } ;
struct TYPE_5__ {int /*<<< orphan*/  object; } ;
struct TYPE_6__ {TYPE_1__ device; } ;
struct nouveau_drm {TYPE_4__* dev; TYPE_2__ client; } ;
struct drm_info_node {TYPE_3__* minor; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EACCES ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvif_rd32 (int /*<<< orphan*/ *,int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nouveau_debugfs_strap_peek(struct seq_file *m, void *data)
{
	struct drm_info_node *node = m->private;
	struct nouveau_drm *drm = nouveau_drm(node->minor->dev);
	int ret;

	ret = pm_runtime_get_sync(drm->dev->dev);
	if (ret < 0 && ret != -EACCES)
		return ret;

	seq_printf(m, "0x%08x\n",
		   nvif_rd32(&drm->client.device.object, 0x101000));

	pm_runtime_mark_last_busy(drm->dev->dev);
	pm_runtime_put_autosuspend(drm->dev->dev);

	return 0;
}