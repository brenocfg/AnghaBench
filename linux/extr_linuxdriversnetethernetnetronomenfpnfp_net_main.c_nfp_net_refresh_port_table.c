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
struct nfp_port {int /*<<< orphan*/  flags; TYPE_1__* app; } ;
struct nfp_pf {int /*<<< orphan*/  port_refresh_work; int /*<<< orphan*/  wq; } ;
struct TYPE_2__ {struct nfp_pf* pf; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_PORT_CHANGED ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nfp_net_refresh_port_table(struct nfp_port *port)
{
	struct nfp_pf *pf = port->app->pf;

	set_bit(NFP_PORT_CHANGED, &port->flags);

	queue_work(pf->wq, &pf->port_refresh_work);
}