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
struct virtqueue {int dummy; } ;
struct viommu_request {size_t buf; size_t len; size_t write_offset; int /*<<< orphan*/  list; scalar_t__ writeback; } ;
struct viommu_dev {int /*<<< orphan*/  requests; int /*<<< orphan*/  request_lock; struct virtqueue** vqs; } ;

/* Variables and functions */
 size_t VIOMMU_REQUEST_VQ ; 
 int /*<<< orphan*/  VIRTIO_IOMMU_S_IOERR ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct viommu_request*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,size_t,size_t) ; 
 int /*<<< orphan*/  viommu_set_req_status (size_t,size_t,int /*<<< orphan*/ ) ; 
 struct viommu_request* virtqueue_get_buf (struct virtqueue*,unsigned int*) ; 
 int /*<<< orphan*/  virtqueue_kick (struct virtqueue*) ; 

__attribute__((used)) static int __viommu_sync_req(struct viommu_dev *viommu)
{
	int ret = 0;
	unsigned int len;
	size_t write_len;
	struct viommu_request *req;
	struct virtqueue *vq = viommu->vqs[VIOMMU_REQUEST_VQ];

	assert_spin_locked(&viommu->request_lock);

	virtqueue_kick(vq);

	while (!list_empty(&viommu->requests)) {
		len = 0;
		req = virtqueue_get_buf(vq, &len);
		if (!req)
			continue;

		if (!len)
			viommu_set_req_status(req->buf, req->len,
					      VIRTIO_IOMMU_S_IOERR);

		write_len = req->len - req->write_offset;
		if (req->writeback && len == write_len)
			memcpy(req->writeback, req->buf + req->write_offset,
			       write_len);

		list_del(&req->list);
		kfree(req);
	}

	return ret;
}