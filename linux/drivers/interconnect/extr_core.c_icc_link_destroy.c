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
struct icc_node {size_t num_links; struct icc_node** links; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (struct icc_node*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  icc_lock ; 
 struct icc_node** krealloc (struct icc_node**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int icc_link_destroy(struct icc_node *src, struct icc_node *dst)
{
	struct icc_node **new;
	size_t slot;
	int ret = 0;

	if (IS_ERR_OR_NULL(src))
		return -EINVAL;

	if (IS_ERR_OR_NULL(dst))
		return -EINVAL;

	mutex_lock(&icc_lock);

	for (slot = 0; slot < src->num_links; slot++)
		if (src->links[slot] == dst)
			break;

	if (WARN_ON(slot == src->num_links)) {
		ret = -ENXIO;
		goto out;
	}

	src->links[slot] = src->links[--src->num_links];

	new = krealloc(src->links, src->num_links * sizeof(*src->links),
		       GFP_KERNEL);
	if (new)
		src->links = new;

out:
	mutex_unlock(&icc_lock);

	return ret;
}