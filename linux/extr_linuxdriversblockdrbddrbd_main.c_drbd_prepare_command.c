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
struct drbd_socket {int dummy; } ;
struct drbd_peer_device {int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 void* conn_prepare_command (int /*<<< orphan*/ ,struct drbd_socket*) ; 

void *drbd_prepare_command(struct drbd_peer_device *peer_device, struct drbd_socket *sock)
{
	return conn_prepare_command(peer_device->connection, sock);
}