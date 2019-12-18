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
struct viommu_request {size_t len; scalar_t__ buf; int /*<<< orphan*/  list; scalar_t__ write_offset; void* writeback; } ;
struct viommu_dev {int /*<<< orphan*/  requests; int /*<<< orphan*/  request_lock; struct virtqueue** vqs; } ;
struct scatterlist {int dummy; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 size_t VIOMMU_REQUEST_VQ ; 
 int /*<<< orphan*/  __viommu_sync_req (struct viommu_dev*) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct viommu_request*) ; 
 struct viommu_request* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,void*,scalar_t__) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,scalar_t__,scalar_t__) ; 
 scalar_t__ viommu_get_write_desc_offset (struct viommu_dev*,void*,size_t) ; 
 int virtqueue_add_sgs (struct virtqueue*,struct scatterlist**,int,int,struct viommu_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __viommu_add_req(struct viommu_dev *viommu, void *buf, size_t len,
			    bool writeback)
{
	int ret;
	off_t write_offset;
	struct viommu_request *req;
	struct scatterlist top_sg, bottom_sg;
	struct scatterlist *sg[2] = { &top_sg, &bottom_sg };
	struct virtqueue *vq = viommu->vqs[VIOMMU_REQUEST_VQ];

	assert_spin_locked(&viommu->request_lock);

	write_offset = viommu_get_write_desc_offset(viommu, buf, len);
	if (write_offset <= 0)
		return -EINVAL;

	req = kzalloc(sizeof(*req) + len, GFP_ATOMIC);
	if (!req)
		return -ENOMEM;

	req->len = len;
	if (writeback) {
		req->writeback = buf + write_offset;
		req->write_offset = write_offset;
	}
	memcpy(&req->buf, buf, write_offset);

	sg_init_one(&top_sg, req->buf, write_offset);
	sg_init_one(&bottom_sg, req->buf + write_offset, len - write_offset);

	ret = virtqueue_add_sgs(vq, sg, 1, 1, req, GFP_ATOMIC);
	if (ret == -ENOSPC) {
		/* If the queue is full, sync and retry */
		if (!__viommu_sync_req(viommu))
			ret = virtqueue_add_sgs(vq, sg, 1, 1, req, GFP_ATOMIC);
	}
	if (ret)
		goto err_free;

	list_add_tail(&req->list, &viommu->requests);
	return 0;

err_free:
	kfree(req);
	return ret;
}