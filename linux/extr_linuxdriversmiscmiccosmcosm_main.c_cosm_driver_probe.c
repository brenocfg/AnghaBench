#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct cosm_device {int sysfs_heartbeat_enable; int /*<<< orphan*/  index; TYPE_3__ dev; int /*<<< orphan*/  state_sysfs; TYPE_2__* sdev; int /*<<< orphan*/  attr_group; int /*<<< orphan*/  scif_work; int /*<<< orphan*/  reset_trigger_work; int /*<<< orphan*/  cosm_mutex; } ;
struct TYPE_6__ {int /*<<< orphan*/  sd; } ;
struct TYPE_7__ {TYPE_1__ kobj; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (TYPE_2__*) ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cosm_create_debug_dir (struct cosm_device*) ; 
 int /*<<< orphan*/  cosm_reset_trigger_work ; 
 int /*<<< orphan*/  cosm_scif_exit () ; 
 int cosm_scif_init () ; 
 int /*<<< orphan*/  cosm_scif_work ; 
 int /*<<< orphan*/  cosm_sysfs_init (struct cosm_device*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 TYPE_2__* device_create_with_groups (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cosm_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_cosm_class ; 
 int /*<<< orphan*/  g_num_dev ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_get_dirent (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cosm_driver_probe(struct cosm_device *cdev)
{
	int rc;

	/* Initialize SCIF server at first probe */
	if (atomic_add_return(1, &g_num_dev) == 1) {
		rc = cosm_scif_init();
		if (rc)
			goto scif_exit;
	}
	mutex_init(&cdev->cosm_mutex);
	INIT_WORK(&cdev->reset_trigger_work, cosm_reset_trigger_work);
	INIT_WORK(&cdev->scif_work, cosm_scif_work);
	cdev->sysfs_heartbeat_enable = true;
	cosm_sysfs_init(cdev);
	cdev->sdev = device_create_with_groups(g_cosm_class, cdev->dev.parent,
			       MKDEV(0, cdev->index), cdev, cdev->attr_group,
			       "mic%d", cdev->index);
	if (IS_ERR(cdev->sdev)) {
		rc = PTR_ERR(cdev->sdev);
		dev_err(&cdev->dev, "device_create_with_groups failed rc %d\n",
			rc);
		goto scif_exit;
	}

	cdev->state_sysfs = sysfs_get_dirent(cdev->sdev->kobj.sd,
		"state");
	if (!cdev->state_sysfs) {
		rc = -ENODEV;
		dev_err(&cdev->dev, "sysfs_get_dirent failed rc %d\n", rc);
		goto destroy_device;
	}
	cosm_create_debug_dir(cdev);
	return 0;
destroy_device:
	device_destroy(g_cosm_class, MKDEV(0, cdev->index));
scif_exit:
	if (atomic_dec_and_test(&g_num_dev))
		cosm_scif_exit();
	return rc;
}