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
struct drbd_connection {int /*<<< orphan*/  cstate; } ;
struct connection_info {int /*<<< orphan*/  conn_role; int /*<<< orphan*/  conn_connection_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  conn_highest_peer (struct drbd_connection*) ; 

__attribute__((used)) static void connection_to_info(struct connection_info *info,
			       struct drbd_connection *connection)
{
	info->conn_connection_state = connection->cstate;
	info->conn_role = conn_highest_peer(connection);
}