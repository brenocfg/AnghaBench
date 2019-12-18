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
struct brcmf_if {int /*<<< orphan*/  pend_8021x_wait; struct brcmf_pub* drvr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_WAIT_FOR_8021X_TX ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*) ; 
 int /*<<< orphan*/  brcmf_get_pend_8021x_cnt (struct brcmf_if*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int brcmf_netdev_wait_pend8021x(struct brcmf_if *ifp)
{
	struct brcmf_pub *drvr = ifp->drvr;
	int err;

	err = wait_event_timeout(ifp->pend_8021x_wait,
				 !brcmf_get_pend_8021x_cnt(ifp),
				 MAX_WAIT_FOR_8021X_TX);

	if (!err)
		bphy_err(drvr, "Timed out waiting for no pending 802.1x packets\n");

	return !err;
}