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
typedef  int /*<<< orphan*/  u32 ;
struct hnae_handle {int q_num; int /*<<< orphan*/ * qs; int /*<<< orphan*/  node; int /*<<< orphan*/  eport_id; struct hnae_buf_ops* bops; struct device* owner_dev; struct hnae_ae_dev* dev; } ;
struct hnae_buf_ops {int dummy; } ;
struct hnae_ae_dev {int /*<<< orphan*/  cls_dev; int /*<<< orphan*/  handle_list; int /*<<< orphan*/  lock; int /*<<< orphan*/  owner; TYPE_1__* ops; } ;
struct fwnode_handle {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct hnae_handle* (* get_handle ) (struct hnae_ae_dev*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct hnae_handle* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct hnae_handle*) ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 struct hnae_ae_dev* find_ae (struct fwnode_handle const*) ; 
 struct hnae_buf_ops hnae_bops ; 
 int /*<<< orphan*/  hnae_fini_queue (int /*<<< orphan*/ ) ; 
 int hnae_init_queue (struct hnae_handle*,int /*<<< orphan*/ ,struct hnae_ae_dev*) ; 
 int /*<<< orphan*/  hnae_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 struct hnae_handle* stub1 (struct hnae_ae_dev*,int /*<<< orphan*/ ) ; 

struct hnae_handle *hnae_get_handle(struct device *owner_dev,
				    const struct fwnode_handle	*fwnode,
				    u32 port_id,
				    struct hnae_buf_ops *bops)
{
	struct hnae_ae_dev *dev;
	struct hnae_handle *handle;
	int i, j;
	int ret;

	dev = find_ae(fwnode);
	if (!dev)
		return ERR_PTR(-ENODEV);

	handle = dev->ops->get_handle(dev, port_id);
	if (IS_ERR(handle)) {
		put_device(&dev->cls_dev);
		return handle;
	}

	handle->dev = dev;
	handle->owner_dev = owner_dev;
	handle->bops = bops ? bops : &hnae_bops;
	handle->eport_id = port_id;

	for (i = 0; i < handle->q_num; i++) {
		ret = hnae_init_queue(handle, handle->qs[i], dev);
		if (ret)
			goto out_when_init_queue;
	}

	__module_get(dev->owner);

	hnae_list_add(&dev->lock, &handle->node, &dev->handle_list);

	return handle;

out_when_init_queue:
	for (j = i - 1; j >= 0; j--)
		hnae_fini_queue(handle->qs[j]);

	put_device(&dev->cls_dev);

	return ERR_PTR(-ENOMEM);
}