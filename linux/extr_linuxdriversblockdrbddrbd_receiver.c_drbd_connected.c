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
struct drbd_peer_device {TYPE_1__* connection; struct drbd_device* device; } ;
struct drbd_device {int /*<<< orphan*/  request_timer; int /*<<< orphan*/  ap_in_flight; int /*<<< orphan*/  flags; int /*<<< orphan*/  own_state_mutex; int /*<<< orphan*/ * state_mutex; scalar_t__ peer_seq; int /*<<< orphan*/  packet_seq; } ;
struct TYPE_2__ {int agreed_pro_version; int /*<<< orphan*/  cstate_mutex; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  RESIZE_PENDING ; 
 int /*<<< orphan*/  USE_DEGR_WFC_T ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drbd_send_current_state (struct drbd_peer_device*) ; 
 int drbd_send_sizes (struct drbd_peer_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drbd_send_sync_param (struct drbd_peer_device*) ; 
 int drbd_send_uuids (struct drbd_peer_device*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

int drbd_connected(struct drbd_peer_device *peer_device)
{
	struct drbd_device *device = peer_device->device;
	int err;

	atomic_set(&device->packet_seq, 0);
	device->peer_seq = 0;

	device->state_mutex = peer_device->connection->agreed_pro_version < 100 ?
		&peer_device->connection->cstate_mutex :
		&device->own_state_mutex;

	err = drbd_send_sync_param(peer_device);
	if (!err)
		err = drbd_send_sizes(peer_device, 0, 0);
	if (!err)
		err = drbd_send_uuids(peer_device);
	if (!err)
		err = drbd_send_current_state(peer_device);
	clear_bit(USE_DEGR_WFC_T, &device->flags);
	clear_bit(RESIZE_PENDING, &device->flags);
	atomic_set(&device->ap_in_flight, 0);
	mod_timer(&device->request_timer, jiffies + HZ); /* just start it here. */
	return err;
}