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
struct xen_vbd {int readonly; int flush_support; int discard_secure; int /*<<< orphan*/  type; struct block_device* bdev; int /*<<< orphan*/  size; int /*<<< orphan*/  pdevice; int /*<<< orphan*/  handle; } ;
struct xen_blkif {int /*<<< orphan*/  domid; struct xen_vbd vbd; } ;
struct request_queue {int /*<<< orphan*/  queue_flags; } ;
struct block_device {TYPE_1__* bd_disk; } ;
typedef  int /*<<< orphan*/  blkif_vdev_t ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  FMODE_READ ; 
 int /*<<< orphan*/  FMODE_WRITE ; 
 int GENHD_FL_CD ; 
 int GENHD_FL_REMOVABLE ; 
 scalar_t__ IS_ERR (struct block_device*) ; 
 int /*<<< orphan*/  MKDEV (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  QUEUE_FLAG_WC ; 
 int /*<<< orphan*/  VDISK_CDROM ; 
 int /*<<< orphan*/  VDISK_REMOVABLE ; 
 struct request_queue* bdev_get_queue (struct block_device*) ; 
 scalar_t__ blk_queue_secure_erase (struct request_queue*) ; 
 struct block_device* blkdev_get_by_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vbd_sz (struct xen_vbd*) ; 
 int /*<<< orphan*/  xen_vbd_free (struct xen_vbd*) ; 

__attribute__((used)) static int xen_vbd_create(struct xen_blkif *blkif, blkif_vdev_t handle,
			  unsigned major, unsigned minor, int readonly,
			  int cdrom)
{
	struct xen_vbd *vbd;
	struct block_device *bdev;
	struct request_queue *q;

	vbd = &blkif->vbd;
	vbd->handle   = handle;
	vbd->readonly = readonly;
	vbd->type     = 0;

	vbd->pdevice  = MKDEV(major, minor);

	bdev = blkdev_get_by_dev(vbd->pdevice, vbd->readonly ?
				 FMODE_READ : FMODE_WRITE, NULL);

	if (IS_ERR(bdev)) {
		pr_warn("xen_vbd_create: device %08x could not be opened\n",
			vbd->pdevice);
		return -ENOENT;
	}

	vbd->bdev = bdev;
	if (vbd->bdev->bd_disk == NULL) {
		pr_warn("xen_vbd_create: device %08x doesn't exist\n",
			vbd->pdevice);
		xen_vbd_free(vbd);
		return -ENOENT;
	}
	vbd->size = vbd_sz(vbd);

	if (vbd->bdev->bd_disk->flags & GENHD_FL_CD || cdrom)
		vbd->type |= VDISK_CDROM;
	if (vbd->bdev->bd_disk->flags & GENHD_FL_REMOVABLE)
		vbd->type |= VDISK_REMOVABLE;

	q = bdev_get_queue(bdev);
	if (q && test_bit(QUEUE_FLAG_WC, &q->queue_flags))
		vbd->flush_support = true;

	if (q && blk_queue_secure_erase(q))
		vbd->discard_secure = true;

	pr_debug("Successful creation of handle=%04x (dom=%u)\n",
		handle, blkif->domid);
	return 0;
}