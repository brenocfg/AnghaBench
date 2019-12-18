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
struct tcpm_port {int connected; int /*<<< orphan*/ * partner; } ;

/* Variables and functions */
 int /*<<< orphan*/  typec_unregister_partner (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tcpm_typec_disconnect(struct tcpm_port *port)
{
	if (port->connected) {
		typec_unregister_partner(port->partner);
		port->partner = NULL;
		port->connected = false;
	}
}