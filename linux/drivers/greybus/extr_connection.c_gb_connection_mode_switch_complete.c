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
struct gb_connection {int mode_switch; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_connection_hd_cport_clear (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_hd_cport_disable (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_svc_connection_destroy (struct gb_connection*) ; 

void gb_connection_mode_switch_complete(struct gb_connection *connection)
{
	gb_connection_svc_connection_destroy(connection);
	gb_connection_hd_cport_clear(connection);

	gb_connection_hd_cport_disable(connection);

	connection->mode_switch = false;
}