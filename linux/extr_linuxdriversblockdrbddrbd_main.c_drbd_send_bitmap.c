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
struct drbd_socket {int /*<<< orphan*/  mutex; scalar_t__ socket; } ;
struct drbd_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* connection; } ;
struct TYPE_3__ {struct drbd_socket data; } ;

/* Variables and functions */
 int /*<<< orphan*/  _drbd_send_bitmap (struct drbd_device*) ; 
 TYPE_2__* first_peer_device (struct drbd_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drbd_send_bitmap(struct drbd_device *device)
{
	struct drbd_socket *sock = &first_peer_device(device)->connection->data;
	int err = -1;

	mutex_lock(&sock->mutex);
	if (sock->socket)
		err = !_drbd_send_bitmap(device);
	mutex_unlock(&sock->mutex);
	return err;
}