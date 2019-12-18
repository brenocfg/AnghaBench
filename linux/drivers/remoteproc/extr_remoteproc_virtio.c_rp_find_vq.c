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
struct virtqueue {struct rproc_vring* priv; } ;
struct virtio_device {int dummy; } ;
struct rproc_vring {int len; struct virtqueue* vq; int /*<<< orphan*/  align; int /*<<< orphan*/  notifyid; } ;
struct rproc_vdev {int rsc_offset; struct rproc_vring* vring; int /*<<< orphan*/  index; } ;
struct rproc_mem_entry {int /*<<< orphan*/  da; void* va; } ;
struct device {int dummy; } ;
struct rproc {scalar_t__ table_ptr; struct device dev; } ;
struct fw_rsc_vdev {TYPE_1__* vring; } ;
struct TYPE_2__ {int /*<<< orphan*/  da; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct rproc_vring*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct virtqueue* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 struct rproc_mem_entry* rproc_find_carveout_by_name (struct rproc*,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  rproc_free_vring (struct rproc_vring*) ; 
 int /*<<< orphan*/  rproc_virtio_notify ; 
 struct rproc* vdev_to_rproc (struct virtio_device*) ; 
 struct rproc_vdev* vdev_to_rvdev (struct virtio_device*) ; 
 struct virtqueue* vring_new_virtqueue (unsigned int,int,int /*<<< orphan*/ ,struct virtio_device*,int,int,void*,int /*<<< orphan*/ ,void (*) (struct virtqueue*),char const*) ; 
 int vring_size (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct virtqueue *rp_find_vq(struct virtio_device *vdev,
				    unsigned int id,
				    void (*callback)(struct virtqueue *vq),
				    const char *name, bool ctx)
{
	struct rproc_vdev *rvdev = vdev_to_rvdev(vdev);
	struct rproc *rproc = vdev_to_rproc(vdev);
	struct device *dev = &rproc->dev;
	struct rproc_mem_entry *mem;
	struct rproc_vring *rvring;
	struct fw_rsc_vdev *rsc;
	struct virtqueue *vq;
	void *addr;
	int len, size;

	/* we're temporarily limited to two virtqueues per rvdev */
	if (id >= ARRAY_SIZE(rvdev->vring))
		return ERR_PTR(-EINVAL);

	if (!name)
		return NULL;

	/* Search allocated memory region by name */
	mem = rproc_find_carveout_by_name(rproc, "vdev%dvring%d", rvdev->index,
					  id);
	if (!mem || !mem->va)
		return ERR_PTR(-ENOMEM);

	rvring = &rvdev->vring[id];
	addr = mem->va;
	len = rvring->len;

	/* zero vring */
	size = vring_size(len, rvring->align);
	memset(addr, 0, size);

	dev_dbg(dev, "vring%d: va %pK qsz %d notifyid %d\n",
		id, addr, len, rvring->notifyid);

	/*
	 * Create the new vq, and tell virtio we're not interested in
	 * the 'weak' smp barriers, since we're talking with a real device.
	 */
	vq = vring_new_virtqueue(id, len, rvring->align, vdev, false, ctx,
				 addr, rproc_virtio_notify, callback, name);
	if (!vq) {
		dev_err(dev, "vring_new_virtqueue %s failed\n", name);
		rproc_free_vring(rvring);
		return ERR_PTR(-ENOMEM);
	}

	rvring->vq = vq;
	vq->priv = rvring;

	/* Update vring in resource table */
	rsc = (void *)rproc->table_ptr + rvdev->rsc_offset;
	rsc->vring[id].da = mem->da;

	return vq;
}