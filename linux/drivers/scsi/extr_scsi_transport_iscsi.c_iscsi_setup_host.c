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
struct transport_container {int dummy; } ;
struct iscsi_cls_host {int /*<<< orphan*/  mutex; int /*<<< orphan*/  nr_scans; } ;
struct device {int dummy; } ;
struct Scsi_Host {struct iscsi_cls_host* shost_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* dev_to_shost (struct device*) ; 
 int /*<<< orphan*/  iscsi_bsg_host_add (struct Scsi_Host*,struct iscsi_cls_host*) ; 
 int /*<<< orphan*/  memset (struct iscsi_cls_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iscsi_setup_host(struct transport_container *tc, struct device *dev,
			    struct device *cdev)
{
	struct Scsi_Host *shost = dev_to_shost(dev);
	struct iscsi_cls_host *ihost = shost->shost_data;

	memset(ihost, 0, sizeof(*ihost));
	atomic_set(&ihost->nr_scans, 0);
	mutex_init(&ihost->mutex);

	iscsi_bsg_host_add(shost, ihost);
	/* ignore any bsg add error - we just can't do sgio */

	return 0;
}