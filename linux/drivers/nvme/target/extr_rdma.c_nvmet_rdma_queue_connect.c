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
struct rdma_cm_id {int /*<<< orphan*/  context; } ;
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;
struct rdma_cm_event {TYPE_1__ param; } ;
struct nvmet_rdma_queue {scalar_t__ host_qid; int /*<<< orphan*/  queue_list; int /*<<< orphan*/  release_work; int /*<<< orphan*/  port; } ;
struct nvmet_rdma_device {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int ECONNREFUSED ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NVME_RDMA_CM_NO_RSC ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nvmet_rdma_queue* nvmet_rdma_alloc_queue (struct nvmet_rdma_device*,struct rdma_cm_id*,struct rdma_cm_event*) ; 
 int nvmet_rdma_cm_accept (struct rdma_cm_id*,struct nvmet_rdma_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_rdma_cm_reject (struct rdma_cm_id*,int /*<<< orphan*/ ) ; 
 struct nvmet_rdma_device* nvmet_rdma_find_get_device (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  nvmet_rdma_free_dev ; 
 int /*<<< orphan*/  nvmet_rdma_queue_list ; 
 int /*<<< orphan*/  nvmet_rdma_queue_mutex ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvmet_rdma_queue_connect(struct rdma_cm_id *cm_id,
		struct rdma_cm_event *event)
{
	struct nvmet_rdma_device *ndev;
	struct nvmet_rdma_queue *queue;
	int ret = -EINVAL;

	ndev = nvmet_rdma_find_get_device(cm_id);
	if (!ndev) {
		nvmet_rdma_cm_reject(cm_id, NVME_RDMA_CM_NO_RSC);
		return -ECONNREFUSED;
	}

	queue = nvmet_rdma_alloc_queue(ndev, cm_id, event);
	if (!queue) {
		ret = -ENOMEM;
		goto put_device;
	}
	queue->port = cm_id->context;

	if (queue->host_qid == 0) {
		/* Let inflight controller teardown complete */
		flush_scheduled_work();
	}

	ret = nvmet_rdma_cm_accept(cm_id, queue, &event->param.conn);
	if (ret) {
		schedule_work(&queue->release_work);
		/* Destroying rdma_cm id is not needed here */
		return 0;
	}

	mutex_lock(&nvmet_rdma_queue_mutex);
	list_add_tail(&queue->queue_list, &nvmet_rdma_queue_list);
	mutex_unlock(&nvmet_rdma_queue_mutex);

	return 0;

put_device:
	kref_put(&ndev->ref, nvmet_rdma_free_dev);

	return ret;
}