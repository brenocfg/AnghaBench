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
struct device {int /*<<< orphan*/  release; int /*<<< orphan*/  parent; } ;
struct ufs_hba {struct request_queue* bsg_queue; struct Scsi_Host* host; struct device bsg_dev; } ;
struct request_queue {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_no; struct device shost_gendev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct request_queue*) ; 
 int PTR_ERR (struct request_queue*) ; 
 struct request_queue* bsg_setup_queue (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*) ; 
 int device_add (struct device*) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  ufs_bsg_node_release ; 
 int /*<<< orphan*/  ufs_bsg_request ; 

int ufs_bsg_probe(struct ufs_hba *hba)
{
	struct device *bsg_dev = &hba->bsg_dev;
	struct Scsi_Host *shost = hba->host;
	struct device *parent = &shost->shost_gendev;
	struct request_queue *q;
	int ret;

	device_initialize(bsg_dev);

	bsg_dev->parent = get_device(parent);
	bsg_dev->release = ufs_bsg_node_release;

	dev_set_name(bsg_dev, "ufs-bsg");

	ret = device_add(bsg_dev);
	if (ret)
		goto out;

	q = bsg_setup_queue(bsg_dev, dev_name(bsg_dev), ufs_bsg_request, NULL, 0);
	if (IS_ERR(q)) {
		ret = PTR_ERR(q);
		goto out;
	}

	hba->bsg_queue = q;

	return 0;

out:
	dev_err(bsg_dev, "fail to initialize a bsg dev %d\n", shost->host_no);
	put_device(bsg_dev);
	return ret;
}