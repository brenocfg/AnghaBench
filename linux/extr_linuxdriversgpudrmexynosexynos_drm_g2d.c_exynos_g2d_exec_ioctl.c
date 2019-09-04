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
struct list_head {int dummy; } ;
struct g2d_runqueue_node {int /*<<< orphan*/  complete; scalar_t__ async; int /*<<< orphan*/  list; struct drm_file* filp; int /*<<< orphan*/  pid; struct list_head event_list; struct list_head run_cmdlist; } ;
struct g2d_data {int /*<<< orphan*/  runqueue_work; int /*<<< orphan*/  g2d_workq; int /*<<< orphan*/  runqueue_mutex; int /*<<< orphan*/  runqueue; int /*<<< orphan*/  runqueue_slab; int /*<<< orphan*/  dev; } ;
struct exynos_drm_private {int /*<<< orphan*/  g2d_dev; } ;
struct drm_file {struct drm_exynos_file_private* driver_priv; } ;
struct drm_exynos_g2d_exec {scalar_t__ async; } ;
struct drm_exynos_file_private {int /*<<< orphan*/  event_list; int /*<<< orphan*/  inuse_cmdlist; } ;
struct drm_device {struct exynos_drm_private* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct g2d_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g2d_free_runqueue_node (struct g2d_data*,struct g2d_runqueue_node*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct g2d_runqueue_node* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct g2d_runqueue_node*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (struct list_head*) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int exynos_g2d_exec_ioctl(struct drm_device *drm_dev, void *data,
			  struct drm_file *file)
{
	struct drm_exynos_file_private *file_priv = file->driver_priv;
	struct exynos_drm_private *priv = drm_dev->dev_private;
	struct g2d_data *g2d = dev_get_drvdata(priv->g2d_dev);
	struct drm_exynos_g2d_exec *req = data;
	struct g2d_runqueue_node *runqueue_node;
	struct list_head *run_cmdlist;
	struct list_head *event_list;

	runqueue_node = kmem_cache_alloc(g2d->runqueue_slab, GFP_KERNEL);
	if (!runqueue_node)
		return -ENOMEM;

	run_cmdlist = &runqueue_node->run_cmdlist;
	event_list = &runqueue_node->event_list;
	INIT_LIST_HEAD(run_cmdlist);
	INIT_LIST_HEAD(event_list);
	init_completion(&runqueue_node->complete);
	runqueue_node->async = req->async;

	list_splice_init(&file_priv->inuse_cmdlist, run_cmdlist);
	list_splice_init(&file_priv->event_list, event_list);

	if (list_empty(run_cmdlist)) {
		dev_err(g2d->dev, "there is no inuse cmdlist\n");
		kmem_cache_free(g2d->runqueue_slab, runqueue_node);
		return -EPERM;
	}

	mutex_lock(&g2d->runqueue_mutex);
	runqueue_node->pid = current->pid;
	runqueue_node->filp = file;
	list_add_tail(&runqueue_node->list, &g2d->runqueue);
	mutex_unlock(&g2d->runqueue_mutex);

	/* Let the runqueue know that there is work to do. */
	queue_work(g2d->g2d_workq, &g2d->runqueue_work);

	if (runqueue_node->async)
		goto out;

	wait_for_completion(&runqueue_node->complete);
	g2d_free_runqueue_node(g2d, runqueue_node);

out:
	return 0;
}