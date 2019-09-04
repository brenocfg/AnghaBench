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
struct drbd_peer_device {int dummy; } ;
struct drbd_connection {int /*<<< orphan*/  peer_devices; } ;

/* Variables and functions */
 struct drbd_peer_device* idr_find (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline struct drbd_peer_device *
conn_peer_device(struct drbd_connection *connection, int volume_number)
{
	return idr_find(&connection->peer_devices, volume_number);
}