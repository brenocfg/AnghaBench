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
struct tcpm_port {int /*<<< orphan*/  vconn_role; TYPE_1__* tcpc; } ;
struct TYPE_2__ {int (* set_vconn ) (TYPE_1__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TYPEC_SINK ; 
 int stub1 (TYPE_1__*,int) ; 

__attribute__((used)) static int tcpm_init_vconn(struct tcpm_port *port)
{
	int ret;

	ret = port->tcpc->set_vconn(port->tcpc, false);
	port->vconn_role = TYPEC_SINK;
	return ret;
}