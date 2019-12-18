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
struct fwnode_handle {int dummy; } ;
struct device {int dummy; } ;
struct coresight_dev_list {int nr_idx; int /*<<< orphan*/  pfx; struct fwnode_handle** fwnode_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ ZERO_OR_NULL_PTR (struct fwnode_handle**) ; 
 int /*<<< orphan*/  coresight_mutex ; 
 int coresight_search_device_idx (struct coresight_dev_list*,struct fwnode_handle*) ; 
 struct fwnode_handle* dev_fwnode (struct device*) ; 
 char* devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct fwnode_handle** krealloc (struct fwnode_handle**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

char *coresight_alloc_device_name(struct coresight_dev_list *dict,
				  struct device *dev)
{
	int idx;
	char *name = NULL;
	struct fwnode_handle **list;

	mutex_lock(&coresight_mutex);

	idx = coresight_search_device_idx(dict, dev_fwnode(dev));
	if (idx < 0) {
		/* Make space for the new entry */
		idx = dict->nr_idx;
		list = krealloc(dict->fwnode_list,
				(idx + 1) * sizeof(*dict->fwnode_list),
				GFP_KERNEL);
		if (ZERO_OR_NULL_PTR(list)) {
			idx = -ENOMEM;
			goto done;
		}

		list[idx] = dev_fwnode(dev);
		dict->fwnode_list = list;
		dict->nr_idx = idx + 1;
	}

	name = devm_kasprintf(dev, GFP_KERNEL, "%s%d", dict->pfx, idx);
done:
	mutex_unlock(&coresight_mutex);
	return name;
}