#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_2__ ret; } ;
struct virtio_pmem_request {int done; int wq_buf_avail; TYPE_1__ resp; int /*<<< orphan*/  host_acked; int /*<<< orphan*/  wq_buf; int /*<<< orphan*/  list; TYPE_2__ req; } ;
struct virtio_pmem {int /*<<< orphan*/  pmem_lock; int /*<<< orphan*/  req_vq; int /*<<< orphan*/  req_list; } ;
struct virtio_device {int /*<<< orphan*/  dev; struct virtio_pmem* priv; } ;
struct scatterlist {int dummy; } ;
struct nd_region {struct virtio_device* provider_data; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VIRTIO_PMEM_REQ_TYPE_FLUSH ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct virtio_pmem_request*) ; 
 struct virtio_pmem_request* kmalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (TYPE_2__) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int virtqueue_add_sgs (int /*<<< orphan*/ ,struct scatterlist**,int,int,struct virtio_pmem_request*,int /*<<< orphan*/ ) ; 
 int virtqueue_kick (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int virtio_pmem_flush(struct nd_region *nd_region)
{
	struct virtio_device *vdev = nd_region->provider_data;
	struct virtio_pmem *vpmem  = vdev->priv;
	struct virtio_pmem_request *req_data;
	struct scatterlist *sgs[2], sg, ret;
	unsigned long flags;
	int err, err1;

	might_sleep();
	req_data = kmalloc(sizeof(*req_data), GFP_KERNEL);
	if (!req_data)
		return -ENOMEM;

	req_data->done = false;
	init_waitqueue_head(&req_data->host_acked);
	init_waitqueue_head(&req_data->wq_buf);
	INIT_LIST_HEAD(&req_data->list);
	req_data->req.type = cpu_to_le32(VIRTIO_PMEM_REQ_TYPE_FLUSH);
	sg_init_one(&sg, &req_data->req, sizeof(req_data->req));
	sgs[0] = &sg;
	sg_init_one(&ret, &req_data->resp.ret, sizeof(req_data->resp));
	sgs[1] = &ret;

	spin_lock_irqsave(&vpmem->pmem_lock, flags);
	 /*
	  * If virtqueue_add_sgs returns -ENOSPC then req_vq virtual
	  * queue does not have free descriptor. We add the request
	  * to req_list and wait for host_ack to wake us up when free
	  * slots are available.
	  */
	while ((err = virtqueue_add_sgs(vpmem->req_vq, sgs, 1, 1, req_data,
					GFP_ATOMIC)) == -ENOSPC) {

		dev_info(&vdev->dev, "failed to send command to virtio pmem device, no free slots in the virtqueue\n");
		req_data->wq_buf_avail = false;
		list_add_tail(&req_data->list, &vpmem->req_list);
		spin_unlock_irqrestore(&vpmem->pmem_lock, flags);

		/* A host response results in "host_ack" getting called */
		wait_event(req_data->wq_buf, req_data->wq_buf_avail);
		spin_lock_irqsave(&vpmem->pmem_lock, flags);
	}
	err1 = virtqueue_kick(vpmem->req_vq);
	spin_unlock_irqrestore(&vpmem->pmem_lock, flags);
	/*
	 * virtqueue_add_sgs failed with error different than -ENOSPC, we can't
	 * do anything about that.
	 */
	if (err || !err1) {
		dev_info(&vdev->dev, "failed to send command to virtio pmem device\n");
		err = -EIO;
	} else {
		/* A host repsonse results in "host_ack" getting called */
		wait_event(req_data->host_acked, req_data->done);
		err = le32_to_cpu(req_data->resp.ret);
	}

	kfree(req_data);
	return err;
}