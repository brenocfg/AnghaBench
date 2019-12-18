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
struct nfp_pf {int /*<<< orphan*/  num_vnics; int /*<<< orphan*/  app; } ;
struct nfp_net {int /*<<< orphan*/  vnic_list; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_app_vnic_free (int /*<<< orphan*/ ,struct nfp_net*) ; 
 int /*<<< orphan*/  nfp_net_free (struct nfp_net*) ; 
 scalar_t__ nfp_net_is_data_vnic (struct nfp_net*) ; 
 int /*<<< orphan*/  nfp_port_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_net_pf_free_vnic(struct nfp_pf *pf, struct nfp_net *nn)
{
	if (nfp_net_is_data_vnic(nn))
		nfp_app_vnic_free(pf->app, nn);
	nfp_port_free(nn->port);
	list_del(&nn->vnic_list);
	pf->num_vnics--;
	nfp_net_free(nn);
}