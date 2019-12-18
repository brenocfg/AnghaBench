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
struct brcmf_pub {int dummy; } ;
struct brcmf_if {int /*<<< orphan*/  vif; struct brcmf_pub* drvr; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ brcmf_fil_iovar_int_set (struct brcmf_if*,char*,int) ; 
 scalar_t__ check_vif_up (int /*<<< orphan*/ ) ; 

void brcmf_set_mpc(struct brcmf_if *ifp, int mpc)
{
	struct brcmf_pub *drvr = ifp->drvr;
	s32 err = 0;

	if (check_vif_up(ifp->vif)) {
		err = brcmf_fil_iovar_int_set(ifp, "mpc", mpc);
		if (err) {
			bphy_err(drvr, "fail to set mpc\n");
			return;
		}
		brcmf_dbg(INFO, "MPC : %d\n", mpc);
	}
}