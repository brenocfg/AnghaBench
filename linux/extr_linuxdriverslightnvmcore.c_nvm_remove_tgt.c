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
struct nvm_target {int dummy; } ;
struct nvm_ioctl_remove {int /*<<< orphan*/  tgtname; } ;
struct nvm_dev {int /*<<< orphan*/  mlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nvm_remove_target (struct nvm_target*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nvm_target* nvm_find_target (struct nvm_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvm_remove_tgt(struct nvm_dev *dev, struct nvm_ioctl_remove *remove)
{
	struct nvm_target *t;

	mutex_lock(&dev->mlock);
	t = nvm_find_target(dev, remove->tgtname);
	if (!t) {
		mutex_unlock(&dev->mlock);
		return 1;
	}
	__nvm_remove_target(t, true);
	mutex_unlock(&dev->mlock);

	return 0;
}