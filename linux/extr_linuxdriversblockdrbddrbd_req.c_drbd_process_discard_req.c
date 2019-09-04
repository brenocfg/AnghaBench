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
struct TYPE_7__ {int size; int /*<<< orphan*/  sector; } ;
struct drbd_request {TYPE_4__* private_bio; TYPE_3__ i; TYPE_2__* device; } ;
struct block_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  bi_status; } ;
struct TYPE_6__ {TYPE_1__* ldev; } ;
struct TYPE_5__ {struct block_device* backing_bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  bio_endio (TYPE_4__*) ; 
 scalar_t__ blkdev_issue_zeroout (struct block_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drbd_process_discard_req(struct drbd_request *req)
{
	struct block_device *bdev = req->device->ldev->backing_bdev;

	if (blkdev_issue_zeroout(bdev, req->i.sector, req->i.size >> 9,
			GFP_NOIO, 0))
		req->private_bio->bi_status = BLK_STS_IOERR;
	bio_endio(req->private_bio);
}