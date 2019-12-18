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
struct mmp_path {int overlay_num; int /*<<< orphan*/  access_ok; TYPE_1__* overlays; int /*<<< orphan*/  node; } ;
struct TYPE_2__ {int /*<<< orphan*/  access_ok; } ;

/* Variables and functions */
 int /*<<< orphan*/  disp_lock ; 
 int /*<<< orphan*/  kfree (struct mmp_path*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mmp_unregister_path(struct mmp_path *path)
{
	int i;

	if (!path)
		return;

	mutex_lock(&disp_lock);
	/* del from pathlist */
	list_del(&path->node);

	/* deinit overlays */
	for (i = 0; i < path->overlay_num; i++)
		mutex_destroy(&path->overlays[i].access_ok);

	mutex_destroy(&path->access_ok);

	kfree(path);
	mutex_unlock(&disp_lock);
}