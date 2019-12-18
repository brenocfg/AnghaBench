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
struct scif_status {int dummy; } ;
struct scif_peer_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  dnode; } ;
struct scif_dev {int /*<<< orphan*/  spdev; int /*<<< orphan*/  node; TYPE_1__* sdev; int /*<<< orphan*/  signal_pool; } ;
typedef  int /*<<< orphan*/  pool_name ;
struct TYPE_4__ {int /*<<< orphan*/  conflock; int /*<<< orphan*/  total; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmam_pool_create (char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 struct scif_peer_dev* rcu_dereference (int /*<<< orphan*/ ) ; 
 TYPE_2__ scif_info ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static int scif_peer_add_device(struct scif_dev *scifdev)
{
	struct scif_peer_dev *spdev = rcu_dereference(scifdev->spdev);
	char pool_name[16];
	int ret;

	ret = device_add(&spdev->dev);
	put_device(&spdev->dev);
	if (ret) {
		dev_err(&scifdev->sdev->dev,
			"dnode %d: peer device_add failed\n", scifdev->node);
		goto put_spdev;
	}

	scnprintf(pool_name, sizeof(pool_name), "scif-%d", spdev->dnode);
	scifdev->signal_pool = dmam_pool_create(pool_name, &scifdev->sdev->dev,
						sizeof(struct scif_status), 1,
						0);
	if (!scifdev->signal_pool) {
		dev_err(&scifdev->sdev->dev,
			"dnode %d: dmam_pool_create failed\n", scifdev->node);
		ret = -ENOMEM;
		goto del_spdev;
	}
	dev_dbg(&spdev->dev, "Added peer dnode %d\n", spdev->dnode);
	return 0;
del_spdev:
	device_del(&spdev->dev);
put_spdev:
	RCU_INIT_POINTER(scifdev->spdev, NULL);
	synchronize_rcu();
	put_device(&spdev->dev);

	mutex_lock(&scif_info.conflock);
	scif_info.total--;
	mutex_unlock(&scif_info.conflock);
	return ret;
}