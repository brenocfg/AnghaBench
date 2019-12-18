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
struct g2d_runqueue_node {scalar_t__ async; int /*<<< orphan*/  complete; struct drm_file* filp; } ;
struct g2d_data {int /*<<< orphan*/  runqueue_mutex; struct g2d_runqueue_node* runqueue_node; struct device* dev; } ;
struct drm_file {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  g2d_free_runqueue_node (struct g2d_data*,struct g2d_runqueue_node*) ; 
 int /*<<< orphan*/  g2d_hw_reset (struct g2d_data*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 

__attribute__((used)) static void g2d_wait_finish(struct g2d_data *g2d, struct drm_file *file)
{
	struct device *dev = g2d->dev;

	struct g2d_runqueue_node *runqueue_node = NULL;
	unsigned int tries = 10;

	mutex_lock(&g2d->runqueue_mutex);

	/* If no node is currently processed, we have nothing to do. */
	if (!g2d->runqueue_node)
		goto out;

	runqueue_node = g2d->runqueue_node;

	/* Check if the currently processed item belongs to us. */
	if (file && runqueue_node->filp != file)
		goto out;

	mutex_unlock(&g2d->runqueue_mutex);

	/* Wait for the G2D engine to finish. */
	while (tries-- && (g2d->runqueue_node == runqueue_node))
		mdelay(10);

	mutex_lock(&g2d->runqueue_mutex);

	if (g2d->runqueue_node != runqueue_node)
		goto out;

	dev_err(dev, "wait timed out, resetting engine...\n");
	g2d_hw_reset(g2d);

	/*
	 * After the hardware reset of the engine we are going to loose
	 * the IRQ which triggers the PM runtime put().
	 * So do this manually here.
	 */
	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);

	complete(&runqueue_node->complete);
	if (runqueue_node->async)
		g2d_free_runqueue_node(g2d, runqueue_node);

out:
	mutex_unlock(&g2d->runqueue_mutex);
}