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
struct mvpp2_port {int nqvecs; int /*<<< orphan*/  comphy; scalar_t__ phylink; TYPE_1__* qvecs; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  mvpp2_interrupts_disable (struct mvpp2_port*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_stop (scalar_t__) ; 

__attribute__((used)) static void mvpp2_stop_dev(struct mvpp2_port *port)
{
	int i;

	/* Disable interrupts on all threads */
	mvpp2_interrupts_disable(port);

	for (i = 0; i < port->nqvecs; i++)
		napi_disable(&port->qvecs[i].napi);

	if (port->phylink)
		phylink_stop(port->phylink);
	phy_power_off(port->comphy);
}