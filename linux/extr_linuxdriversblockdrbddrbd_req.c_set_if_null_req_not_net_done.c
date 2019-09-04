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
struct drbd_request {int dummy; } ;
struct drbd_peer_device {struct drbd_connection* connection; } ;
struct drbd_connection {struct drbd_request* req_not_net_done; } ;

/* Variables and functions */

__attribute__((used)) static void set_if_null_req_not_net_done(struct drbd_peer_device *peer_device, struct drbd_request *req)
{
	struct drbd_connection *connection = peer_device ? peer_device->connection : NULL;
	if (!connection)
		return;
	if (connection->req_not_net_done == NULL)
		connection->req_not_net_done = req;
}