#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfp_repr {struct nfp_abm_link* app_priv; } ;
struct nfp_port {scalar_t__ type; int /*<<< orphan*/  netdev; } ;
struct nfp_app {int dummy; } ;
struct nfp_abm_link {TYPE_2__* vnic; } ;
struct TYPE_3__ {int num_r_vecs; } ;
struct TYPE_4__ {TYPE_1__ dp; } ;

/* Variables and functions */
 scalar_t__ NFP_PORT_PF_PORT ; 
 struct nfp_repr* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_abm_port_get_stats_count(struct nfp_app *app, struct nfp_port *port)
{
	struct nfp_repr *repr = netdev_priv(port->netdev);
	struct nfp_abm_link *alink;

	if (port->type != NFP_PORT_PF_PORT)
		return 0;
	alink = repr->app_priv;
	return alink->vnic->dp.num_r_vecs * 2;
}