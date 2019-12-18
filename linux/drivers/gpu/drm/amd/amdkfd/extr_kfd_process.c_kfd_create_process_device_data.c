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
struct TYPE_2__ {scalar_t__ evicted; int /*<<< orphan*/ * pqm; int /*<<< orphan*/  dqm; int /*<<< orphan*/  priv_queue_list; int /*<<< orphan*/  queues_list; } ;
struct kfd_process_device {int already_dequeued; int /*<<< orphan*/  alloc_idr; int /*<<< orphan*/  per_device_list; int /*<<< orphan*/  bound; struct kfd_process* process; TYPE_1__ qpd; struct kfd_dev* dev; } ;
struct kfd_process {int /*<<< orphan*/  per_device_data; int /*<<< orphan*/  pqm; } ;
struct kfd_dev {int /*<<< orphan*/  dqm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PDD_UNBOUND ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ init_doorbell_bitmap (TYPE_1__*,struct kfd_dev*) ; 
 int /*<<< orphan*/  kfree (struct kfd_process_device*) ; 
 struct kfd_process_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

struct kfd_process_device *kfd_create_process_device_data(struct kfd_dev *dev,
							struct kfd_process *p)
{
	struct kfd_process_device *pdd = NULL;

	pdd = kzalloc(sizeof(*pdd), GFP_KERNEL);
	if (!pdd)
		return NULL;

	if (init_doorbell_bitmap(&pdd->qpd, dev)) {
		pr_err("Failed to init doorbell for process\n");
		kfree(pdd);
		return NULL;
	}

	pdd->dev = dev;
	INIT_LIST_HEAD(&pdd->qpd.queues_list);
	INIT_LIST_HEAD(&pdd->qpd.priv_queue_list);
	pdd->qpd.dqm = dev->dqm;
	pdd->qpd.pqm = &p->pqm;
	pdd->qpd.evicted = 0;
	pdd->process = p;
	pdd->bound = PDD_UNBOUND;
	pdd->already_dequeued = false;
	list_add(&pdd->per_device_list, &p->per_device_data);

	/* Init idr used for memory handle translation */
	idr_init(&pdd->alloc_idr);

	return pdd;
}