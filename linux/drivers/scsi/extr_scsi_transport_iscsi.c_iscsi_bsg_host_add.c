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
struct request_queue {int dummy; } ;
struct iscsi_internal {TYPE_1__* iscsi_transport; } ;
struct iscsi_cls_host {struct request_queue* bsg_q; } ;
struct device {int dummy; } ;
struct Scsi_Host {int host_no; int /*<<< orphan*/  transportt; struct device shost_gendev; } ;
typedef  int /*<<< orphan*/  bsg_name ;
struct TYPE_2__ {int /*<<< orphan*/  bsg_request; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 scalar_t__ IS_ERR (struct request_queue*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int PTR_ERR (struct request_queue*) ; 
 int /*<<< orphan*/  __scsi_init_queue (struct Scsi_Host*,struct request_queue*) ; 
 struct request_queue* bsg_setup_queue (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_bsg_host_dispatch ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 struct iscsi_internal* to_iscsi_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iscsi_bsg_host_add(struct Scsi_Host *shost, struct iscsi_cls_host *ihost)
{
	struct device *dev = &shost->shost_gendev;
	struct iscsi_internal *i = to_iscsi_internal(shost->transportt);
	struct request_queue *q;
	char bsg_name[20];

	if (!i->iscsi_transport->bsg_request)
		return -ENOTSUPP;

	snprintf(bsg_name, sizeof(bsg_name), "iscsi_host%d", shost->host_no);
	q = bsg_setup_queue(dev, bsg_name, iscsi_bsg_host_dispatch, NULL, 0);
	if (IS_ERR(q)) {
		shost_printk(KERN_ERR, shost, "bsg interface failed to "
			     "initialize - no request queue\n");
		return PTR_ERR(q);
	}
	__scsi_init_queue(shost, q);

	ihost->bsg_q = q;
	return 0;
}