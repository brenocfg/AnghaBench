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
struct nfp_abm {int /*<<< orphan*/  eswitch_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ESWITCH_MODE_LEGACY ; 
 int /*<<< orphan*/  nfp_abm_ctrl_qm_disable (struct nfp_abm*) ; 
 int /*<<< orphan*/  nfp_abm_kill_reprs_all (struct nfp_abm*) ; 

__attribute__((used)) static int nfp_abm_eswitch_set_legacy(struct nfp_abm *abm)
{
	nfp_abm_kill_reprs_all(abm);
	nfp_abm_ctrl_qm_disable(abm);

	abm->eswitch_mode = DEVLINK_ESWITCH_MODE_LEGACY;
	return 0;
}