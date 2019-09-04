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
struct nfp_pf {int /*<<< orphan*/  ctrl_vnic; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfp_ctrl_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_pf_clean_vnic (struct nfp_pf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_net_pf_app_stop_ctrl(struct nfp_pf *pf)
{
	if (!pf->ctrl_vnic)
		return;
	nfp_ctrl_close(pf->ctrl_vnic);
	nfp_net_pf_clean_vnic(pf, pf->ctrl_vnic);
}