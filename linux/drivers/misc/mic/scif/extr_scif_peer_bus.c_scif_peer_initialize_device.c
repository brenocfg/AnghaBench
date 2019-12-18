#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * bus; int /*<<< orphan*/  release; int /*<<< orphan*/  parent; } ;
struct scif_peer_dev {int /*<<< orphan*/  dnode; TYPE_3__ dev; } ;
struct scif_dev {int /*<<< orphan*/  node; TYPE_1__* sdev; int /*<<< orphan*/  spdev; } ;
struct TYPE_10__ {int /*<<< orphan*/  parent; } ;
struct TYPE_8__ {int /*<<< orphan*/  conflock; int /*<<< orphan*/  maxid; int /*<<< orphan*/  total; } ;
struct TYPE_7__ {TYPE_6__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_initialize (TYPE_3__*) ; 
 int /*<<< orphan*/  get_device (TYPE_3__*) ; 
 struct scif_peer_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct scif_peer_dev*) ; 
 TYPE_2__ scif_info ; 
 int /*<<< orphan*/  scif_peer_bus ; 
 int /*<<< orphan*/  scif_peer_release_dev ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static int scif_peer_initialize_device(struct scif_dev *scifdev)
{
	struct scif_peer_dev *spdev;
	int ret;

	spdev = kzalloc(sizeof(*spdev), GFP_KERNEL);
	if (!spdev) {
		ret = -ENOMEM;
		goto err;
	}

	spdev->dev.parent = scifdev->sdev->dev.parent;
	spdev->dev.release = scif_peer_release_dev;
	spdev->dnode = scifdev->node;
	spdev->dev.bus = &scif_peer_bus;
	dev_set_name(&spdev->dev, "scif_peer-dev%u", spdev->dnode);

	device_initialize(&spdev->dev);
	get_device(&spdev->dev);
	rcu_assign_pointer(scifdev->spdev, spdev);

	mutex_lock(&scif_info.conflock);
	scif_info.total++;
	scif_info.maxid = max_t(u32, spdev->dnode, scif_info.maxid);
	mutex_unlock(&scif_info.conflock);
	return 0;
err:
	dev_err(&scifdev->sdev->dev,
		"dnode %d: initialize_device rc %d\n", scifdev->node, ret);
	return ret;
}