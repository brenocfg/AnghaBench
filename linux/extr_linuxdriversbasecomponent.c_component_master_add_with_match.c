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
struct master {int /*<<< orphan*/  node; struct component_match* match; struct component_master_ops const* ops; struct device* dev; } ;
struct device {int dummy; } ;
struct component_match {int /*<<< orphan*/  num; } ;
struct component_master_ops {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  component_master_debugfs_add (struct master*) ; 
 int component_match_realloc (struct device*,struct component_match*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  component_mutex ; 
 int /*<<< orphan*/  free_master (struct master*) ; 
 struct master* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  masters ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int try_to_bring_up_master (struct master*,int /*<<< orphan*/ *) ; 

int component_master_add_with_match(struct device *dev,
	const struct component_master_ops *ops,
	struct component_match *match)
{
	struct master *master;
	int ret;

	/* Reallocate the match array for its true size */
	ret = component_match_realloc(dev, match, match->num);
	if (ret)
		return ret;

	master = kzalloc(sizeof(*master), GFP_KERNEL);
	if (!master)
		return -ENOMEM;

	master->dev = dev;
	master->ops = ops;
	master->match = match;

	component_master_debugfs_add(master);
	/* Add to the list of available masters. */
	mutex_lock(&component_mutex);
	list_add(&master->node, &masters);

	ret = try_to_bring_up_master(master, NULL);

	if (ret < 0)
		free_master(master);

	mutex_unlock(&component_mutex);

	return ret < 0 ? ret : 0;
}