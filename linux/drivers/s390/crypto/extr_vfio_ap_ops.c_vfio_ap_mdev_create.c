#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mdev_device {int dummy; } ;
struct kobject {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  hook; } ;
struct ap_matrix_mdev {int /*<<< orphan*/  node; TYPE_1__ pqap_hook; int /*<<< orphan*/  matrix; struct mdev_device* mdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  mdev_list; int /*<<< orphan*/  info; int /*<<< orphan*/  available_instances; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ atomic_dec_if_positive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_pqap ; 
 struct ap_matrix_mdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* matrix_dev ; 
 int /*<<< orphan*/  mdev_set_drvdata (struct mdev_device*,struct ap_matrix_mdev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfio_ap_matrix_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vfio_ap_mdev_create(struct kobject *kobj, struct mdev_device *mdev)
{
	struct ap_matrix_mdev *matrix_mdev;

	if ((atomic_dec_if_positive(&matrix_dev->available_instances) < 0))
		return -EPERM;

	matrix_mdev = kzalloc(sizeof(*matrix_mdev), GFP_KERNEL);
	if (!matrix_mdev) {
		atomic_inc(&matrix_dev->available_instances);
		return -ENOMEM;
	}

	matrix_mdev->mdev = mdev;
	vfio_ap_matrix_init(&matrix_dev->info, &matrix_mdev->matrix);
	mdev_set_drvdata(mdev, matrix_mdev);
	matrix_mdev->pqap_hook.hook = handle_pqap;
	matrix_mdev->pqap_hook.owner = THIS_MODULE;
	mutex_lock(&matrix_dev->lock);
	list_add(&matrix_mdev->node, &matrix_dev->mdev_list);
	mutex_unlock(&matrix_dev->lock);

	return 0;
}