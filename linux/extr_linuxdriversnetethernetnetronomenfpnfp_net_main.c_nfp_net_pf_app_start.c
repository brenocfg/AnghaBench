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
struct nfp_pf {int /*<<< orphan*/  app; scalar_t__ num_vfs; int /*<<< orphan*/  ctrl_vnic; } ;

/* Variables and functions */
 int nfp_app_sriov_enable (int /*<<< orphan*/ ,scalar_t__) ; 
 int nfp_app_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_app_stop (int /*<<< orphan*/ ) ; 
 int nfp_net_pf_app_start_ctrl (struct nfp_pf*) ; 
 int /*<<< orphan*/  nfp_net_pf_app_stop_ctrl (struct nfp_pf*) ; 

__attribute__((used)) static int nfp_net_pf_app_start(struct nfp_pf *pf)
{
	int err;

	err = nfp_net_pf_app_start_ctrl(pf);
	if (err)
		return err;

	err = nfp_app_start(pf->app, pf->ctrl_vnic);
	if (err)
		goto err_ctrl_stop;

	if (pf->num_vfs) {
		err = nfp_app_sriov_enable(pf->app, pf->num_vfs);
		if (err)
			goto err_app_stop;
	}

	return 0;

err_app_stop:
	nfp_app_stop(pf->app);
err_ctrl_stop:
	nfp_net_pf_app_stop_ctrl(pf);
	return err;
}