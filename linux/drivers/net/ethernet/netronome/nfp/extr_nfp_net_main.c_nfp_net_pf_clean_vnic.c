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
struct nfp_pf {int /*<<< orphan*/  app; } ;
struct nfp_net {scalar_t__ port; int /*<<< orphan*/  debugfs_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfp_app_vnic_clean (int /*<<< orphan*/ ,struct nfp_net*) ; 
 int /*<<< orphan*/  nfp_devlink_port_type_clear (scalar_t__) ; 
 int /*<<< orphan*/  nfp_devlink_port_unregister (scalar_t__) ; 
 int /*<<< orphan*/  nfp_net_clean (struct nfp_net*) ; 
 int /*<<< orphan*/  nfp_net_debugfs_dir_clean (int /*<<< orphan*/ *) ; 
 scalar_t__ nfp_net_is_data_vnic (struct nfp_net*) ; 

__attribute__((used)) static void nfp_net_pf_clean_vnic(struct nfp_pf *pf, struct nfp_net *nn)
{
	if (nfp_net_is_data_vnic(nn))
		nfp_app_vnic_clean(pf->app, nn);
	if (nn->port)
		nfp_devlink_port_type_clear(nn->port);
	nfp_net_debugfs_dir_clean(&nn->debugfs_dir);
	nfp_net_clean(nn);
	if (nn->port)
		nfp_devlink_port_unregister(nn->port);
}