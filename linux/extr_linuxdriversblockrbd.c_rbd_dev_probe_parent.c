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
struct rbd_device {int /*<<< orphan*/  parent_ref; struct rbd_device* parent; int /*<<< orphan*/  parent_spec; int /*<<< orphan*/  rbd_client; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int RBD_MAX_PARENT_CHAIN_LEN ; 
 struct rbd_device* __rbd_dev_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __rbd_get_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  rbd_dev_destroy (struct rbd_device*) ; 
 int rbd_dev_image_probe (struct rbd_device*,int) ; 
 int /*<<< orphan*/  rbd_dev_unparent (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_spec_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rbd_dev_probe_parent(struct rbd_device *rbd_dev, int depth)
{
	struct rbd_device *parent = NULL;
	int ret;

	if (!rbd_dev->parent_spec)
		return 0;

	if (++depth > RBD_MAX_PARENT_CHAIN_LEN) {
		pr_info("parent chain is too long (%d)\n", depth);
		ret = -EINVAL;
		goto out_err;
	}

	parent = __rbd_dev_create(rbd_dev->rbd_client, rbd_dev->parent_spec);
	if (!parent) {
		ret = -ENOMEM;
		goto out_err;
	}

	/*
	 * Images related by parent/child relationships always share
	 * rbd_client and spec/parent_spec, so bump their refcounts.
	 */
	__rbd_get_client(rbd_dev->rbd_client);
	rbd_spec_get(rbd_dev->parent_spec);

	ret = rbd_dev_image_probe(parent, depth);
	if (ret < 0)
		goto out_err;

	rbd_dev->parent = parent;
	atomic_set(&rbd_dev->parent_ref, 1);
	return 0;

out_err:
	rbd_dev_unparent(rbd_dev);
	rbd_dev_destroy(parent);
	return ret;
}