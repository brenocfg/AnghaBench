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
struct TYPE_2__ {struct cxgbit_device* cdev; } ;
struct cxgbit_np {TYPE_1__ com; } ;
struct cxgbit_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ __cxgbit_setup_cdev_np (struct cxgbit_device*,struct cxgbit_np*) ; 
 int /*<<< orphan*/  cdev_list_lock ; 
 struct cxgbit_device* cxgbit_find_np_cdev (struct cxgbit_np*) ; 
 scalar_t__ cxgbit_np_hash_find (struct cxgbit_device*,struct cxgbit_np*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cxgbit_setup_cdev_np(struct cxgbit_np *cnp)
{
	struct cxgbit_device *cdev;
	int ret = -1;

	mutex_lock(&cdev_list_lock);
	cdev = cxgbit_find_np_cdev(cnp);
	if (!cdev)
		goto out;

	if (cxgbit_np_hash_find(cdev, cnp) >= 0)
		goto out;

	if (__cxgbit_setup_cdev_np(cdev, cnp))
		goto out;

	cnp->com.cdev = cdev;
	ret = 0;
out:
	mutex_unlock(&cdev_list_lock);
	return ret;
}