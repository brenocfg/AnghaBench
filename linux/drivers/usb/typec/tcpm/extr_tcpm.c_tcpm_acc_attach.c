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
struct tcpm_port {int attached; int /*<<< orphan*/ * partner; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPEC_HOST ; 
 int /*<<< orphan*/  TYPEC_SOURCE ; 
 int tcpm_set_roles (struct tcpm_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_typec_connect (struct tcpm_port*) ; 

__attribute__((used)) static int tcpm_acc_attach(struct tcpm_port *port)
{
	int ret;

	if (port->attached)
		return 0;

	ret = tcpm_set_roles(port, true, TYPEC_SOURCE, TYPEC_HOST);
	if (ret < 0)
		return ret;

	port->partner = NULL;

	tcpm_typec_connect(port);

	port->attached = true;

	return 0;
}