#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sas_rphy {struct request_queue* q; int /*<<< orphan*/  dev; } ;
struct request_queue {int dummy; } ;
struct Scsi_Host {int host_no; int /*<<< orphan*/  shost_gendev; TYPE_2__* hostt; int /*<<< orphan*/  transportt; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_8__ {struct request_queue* q; } ;
struct TYPE_7__ {TYPE_1__* f; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  smp_handler; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct request_queue*) ; 
 int PTR_ERR (struct request_queue*) ; 
 struct request_queue* bsg_setup_queue (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_smp_dispatch ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 TYPE_4__* to_sas_host_attrs (struct Scsi_Host*) ; 
 TYPE_3__* to_sas_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sas_bsg_initialize(struct Scsi_Host *shost, struct sas_rphy *rphy)
{
	struct request_queue *q;

	if (!to_sas_internal(shost->transportt)->f->smp_handler) {
		printk("%s can't handle SMP requests\n", shost->hostt->name);
		return 0;
	}

	if (rphy) {
		q = bsg_setup_queue(&rphy->dev, dev_name(&rphy->dev),
				sas_smp_dispatch, NULL, 0);
		if (IS_ERR(q))
			return PTR_ERR(q);
		rphy->q = q;
	} else {
		char name[20];

		snprintf(name, sizeof(name), "sas_host%d", shost->host_no);
		q = bsg_setup_queue(&shost->shost_gendev, name,
				sas_smp_dispatch, NULL, 0);
		if (IS_ERR(q))
			return PTR_ERR(q);
		to_sas_host_attrs(shost)->q = q;
	}

	return 0;
}