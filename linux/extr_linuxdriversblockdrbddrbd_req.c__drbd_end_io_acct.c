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
struct request_queue {int dummy; } ;
struct drbd_request {int /*<<< orphan*/  start_jif; int /*<<< orphan*/  master_bio; } ;
struct drbd_device {TYPE_1__* vdisk; struct request_queue* rq_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  part0; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_end_io_acct (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _drbd_end_io_acct(struct drbd_device *device, struct drbd_request *req)
{
	struct request_queue *q = device->rq_queue;

	generic_end_io_acct(q, bio_op(req->master_bio),
			    &device->vdisk->part0, req->start_jif);
}