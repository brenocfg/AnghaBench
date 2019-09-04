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
struct request_queue {scalar_t__ queuedata; } ;
struct drbd_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_size; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  int /*<<< orphan*/  blk_qc_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_QC_T_NONE ; 
 int /*<<< orphan*/  D_ASSERT (struct drbd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __drbd_make_request (struct drbd_device*,struct bio*,unsigned long) ; 
 int /*<<< orphan*/  blk_queue_split (struct request_queue*,struct bio**) ; 
 int /*<<< orphan*/  inc_ap_bio (struct drbd_device*) ; 
 unsigned long jiffies ; 

blk_qc_t drbd_make_request(struct request_queue *q, struct bio *bio)
{
	struct drbd_device *device = (struct drbd_device *) q->queuedata;
	unsigned long start_jif;

	blk_queue_split(q, &bio);

	start_jif = jiffies;

	/*
	 * what we "blindly" assume:
	 */
	D_ASSERT(device, IS_ALIGNED(bio->bi_iter.bi_size, 512));

	inc_ap_bio(device);
	__drbd_make_request(device, bio, start_jif);
	return BLK_QC_T_NONE;
}