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
struct TYPE_7__ {int /*<<< orphan*/  sector; int /*<<< orphan*/  size; } ;
struct drbd_request {int /*<<< orphan*/ * private_bio; TYPE_3__ i; struct drbd_device* device; } ;
struct TYPE_5__ {scalar_t__ pdsk; } ;
struct drbd_device {TYPE_2__* ldev; TYPE_1__ state; } ;
typedef  enum drbd_read_balancing { ____Placeholder_drbd_read_balancing } drbd_read_balancing ;
struct TYPE_8__ {int read_balancing; } ;
struct TYPE_6__ {int /*<<< orphan*/  disk_conf; } ;

/* Variables and functions */
 scalar_t__ D_UP_TO_DATE ; 
 int RB_PREFER_LOCAL ; 
 int /*<<< orphan*/  bio_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drbd_may_do_local_read (struct drbd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 
 TYPE_4__* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ remote_due_to_read_balancing (struct drbd_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool do_remote_read(struct drbd_request *req)
{
	struct drbd_device *device = req->device;
	enum drbd_read_balancing rbm;

	if (req->private_bio) {
		if (!drbd_may_do_local_read(device,
					req->i.sector, req->i.size)) {
			bio_put(req->private_bio);
			req->private_bio = NULL;
			put_ldev(device);
		}
	}

	if (device->state.pdsk != D_UP_TO_DATE)
		return false;

	if (req->private_bio == NULL)
		return true;

	/* TODO: improve read balancing decisions, take into account drbd
	 * protocol, pending requests etc. */

	rcu_read_lock();
	rbm = rcu_dereference(device->ldev->disk_conf)->read_balancing;
	rcu_read_unlock();

	if (rbm == RB_PREFER_LOCAL && req->private_bio)
		return false; /* submit locally */

	if (remote_due_to_read_balancing(device, req->i.sector, rbm)) {
		if (req->private_bio) {
			bio_put(req->private_bio);
			req->private_bio = NULL;
			put_ldev(device);
		}
		return true;
	}

	return false;
}