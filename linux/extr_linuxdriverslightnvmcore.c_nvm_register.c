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
struct nvm_dev {int /*<<< orphan*/  dma_pool; TYPE_1__* ops; int /*<<< orphan*/  devices; int /*<<< orphan*/  q; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy_dma_pool ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* create_dma_pool ) (struct nvm_dev*,char*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvm_devices ; 
 int nvm_init (struct nvm_dev*) ; 
 int /*<<< orphan*/  nvm_lock ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  stub1 (struct nvm_dev*,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int nvm_register(struct nvm_dev *dev)
{
	int ret;

	if (!dev->q || !dev->ops)
		return -EINVAL;

	dev->dma_pool = dev->ops->create_dma_pool(dev, "ppalist");
	if (!dev->dma_pool) {
		pr_err("nvm: could not create dma pool\n");
		return -ENOMEM;
	}

	ret = nvm_init(dev);
	if (ret)
		goto err_init;

	/* register device with a supported media manager */
	down_write(&nvm_lock);
	list_add(&dev->devices, &nvm_devices);
	up_write(&nvm_lock);

	return 0;
err_init:
	dev->ops->destroy_dma_pool(dev->dma_pool);
	return ret;
}