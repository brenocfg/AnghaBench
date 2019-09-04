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
struct drbd_device {int /*<<< orphan*/  net_ee; int /*<<< orphan*/  done_ee; int /*<<< orphan*/  read_ee; int /*<<< orphan*/  sync_ee; int /*<<< orphan*/  active_ee; } ;

/* Variables and functions */
 int /*<<< orphan*/  drbd_err (struct drbd_device*,char*,int) ; 
 int drbd_free_peer_reqs (struct drbd_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drbd_release_all_peer_reqs(struct drbd_device *device)
{
	int rr;

	rr = drbd_free_peer_reqs(device, &device->active_ee);
	if (rr)
		drbd_err(device, "%d EEs in active list found!\n", rr);

	rr = drbd_free_peer_reqs(device, &device->sync_ee);
	if (rr)
		drbd_err(device, "%d EEs in sync list found!\n", rr);

	rr = drbd_free_peer_reqs(device, &device->read_ee);
	if (rr)
		drbd_err(device, "%d EEs in read list found!\n", rr);

	rr = drbd_free_peer_reqs(device, &device->done_ee);
	if (rr)
		drbd_err(device, "%d EEs in done list found!\n", rr);

	rr = drbd_free_peer_reqs(device, &device->net_ee);
	if (rr)
		drbd_err(device, "%d EEs in net list found!\n", rr);
}