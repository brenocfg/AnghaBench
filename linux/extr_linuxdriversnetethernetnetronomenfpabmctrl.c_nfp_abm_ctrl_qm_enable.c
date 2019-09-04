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
struct nfp_abm {TYPE_1__* app; } ;
struct TYPE_2__ {int /*<<< orphan*/  pf; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_MBOX_PCIE_ABM_ENABLE ; 
 int nfp_mbox_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int nfp_abm_ctrl_qm_enable(struct nfp_abm *abm)
{
	return nfp_mbox_cmd(abm->app->pf, NFP_MBOX_PCIE_ABM_ENABLE,
			    NULL, 0, NULL, 0);
}