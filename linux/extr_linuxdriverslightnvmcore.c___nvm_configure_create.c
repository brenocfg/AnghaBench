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
struct nvm_ioctl_create {int /*<<< orphan*/  dev; } ;
struct nvm_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int nvm_create_tgt (struct nvm_dev*,struct nvm_ioctl_create*) ; 
 struct nvm_dev* nvm_find_nvm_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvm_lock ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __nvm_configure_create(struct nvm_ioctl_create *create)
{
	struct nvm_dev *dev;

	down_write(&nvm_lock);
	dev = nvm_find_nvm_dev(create->dev);
	up_write(&nvm_lock);

	if (!dev) {
		pr_err("nvm: device not found\n");
		return -EINVAL;
	}

	return nvm_create_tgt(dev, create);
}