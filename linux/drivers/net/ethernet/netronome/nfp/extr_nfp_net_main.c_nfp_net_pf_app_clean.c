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
struct nfp_pf {int /*<<< orphan*/ * app; int /*<<< orphan*/  lock; int /*<<< orphan*/  ctrl_vnic_bar; scalar_t__ ctrl_vnic; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_app_clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_app_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_cpp_area_release_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_pf_free_vnic (struct nfp_pf*,scalar_t__) ; 

__attribute__((used)) static void nfp_net_pf_app_clean(struct nfp_pf *pf)
{
	if (pf->ctrl_vnic) {
		nfp_net_pf_free_vnic(pf, pf->ctrl_vnic);
		nfp_cpp_area_release_free(pf->ctrl_vnic_bar);
	}

	mutex_lock(&pf->lock);
	nfp_app_clean(pf->app);
	mutex_unlock(&pf->lock);

	nfp_app_free(pf->app);
	pf->app = NULL;
}