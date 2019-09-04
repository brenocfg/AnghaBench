#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xenbus_transaction {int dummy; } ;
struct xenbus_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  nodename; } ;
struct TYPE_4__ {int discard_secure; struct block_device* bdev; } ;
struct xen_blkif {TYPE_2__ vbd; } ;
struct TYPE_3__ {int discard_granularity; int discard_alignment; } ;
struct request_queue {TYPE_1__ limits; } ;
struct block_device {int dummy; } ;
struct backend_info {struct xen_blkif* blkif; struct xenbus_device* dev; } ;

/* Variables and functions */
 struct request_queue* bdev_get_queue (struct block_device*) ; 
 scalar_t__ blk_queue_discard (struct request_queue*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int xenbus_printf (struct xenbus_transaction,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  xenbus_read_unsigned (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void xen_blkbk_discard(struct xenbus_transaction xbt, struct backend_info *be)
{
	struct xenbus_device *dev = be->dev;
	struct xen_blkif *blkif = be->blkif;
	int err;
	int state = 0;
	struct block_device *bdev = be->blkif->vbd.bdev;
	struct request_queue *q = bdev_get_queue(bdev);

	if (!xenbus_read_unsigned(dev->nodename, "discard-enable", 1))
		return;

	if (blk_queue_discard(q)) {
		err = xenbus_printf(xbt, dev->nodename,
			"discard-granularity", "%u",
			q->limits.discard_granularity);
		if (err) {
			dev_warn(&dev->dev, "writing discard-granularity (%d)", err);
			return;
		}
		err = xenbus_printf(xbt, dev->nodename,
			"discard-alignment", "%u",
			q->limits.discard_alignment);
		if (err) {
			dev_warn(&dev->dev, "writing discard-alignment (%d)", err);
			return;
		}
		state = 1;
		/* Optional. */
		err = xenbus_printf(xbt, dev->nodename,
				    "discard-secure", "%d",
				    blkif->vbd.discard_secure);
		if (err) {
			dev_warn(&dev->dev, "writing discard-secure (%d)", err);
			return;
		}
	}
	err = xenbus_printf(xbt, dev->nodename, "feature-discard",
			    "%d", state);
	if (err)
		dev_warn(&dev->dev, "writing feature-discard (%d)", err);
}