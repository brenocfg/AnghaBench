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
struct nfp_pf {int /*<<< orphan*/  app; scalar_t__ num_vfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfp_app_sriov_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_app_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_pf_app_stop_ctrl (struct nfp_pf*) ; 

__attribute__((used)) static void nfp_net_pf_app_stop(struct nfp_pf *pf)
{
	if (pf->num_vfs)
		nfp_app_sriov_disable(pf->app);
	nfp_app_stop(pf->app);
	nfp_net_pf_app_stop_ctrl(pf);
}