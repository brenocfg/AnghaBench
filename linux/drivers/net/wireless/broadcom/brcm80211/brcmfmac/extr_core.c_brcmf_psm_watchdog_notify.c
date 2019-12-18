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
struct brcmf_pub {int /*<<< orphan*/  bus_if; } ;
struct brcmf_if {struct brcmf_pub* drvr; int /*<<< orphan*/  bsscfgidx; } ;
struct brcmf_event_msg {int /*<<< orphan*/  datalen; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,...) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int brcmf_debug_create_memdump (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_psm_watchdog_notify(struct brcmf_if *ifp,
				     const struct brcmf_event_msg *evtmsg,
				     void *data)
{
	struct brcmf_pub *drvr = ifp->drvr;
	int err;

	brcmf_dbg(TRACE, "enter: bsscfgidx=%d\n", ifp->bsscfgidx);

	bphy_err(drvr, "PSM's watchdog has fired!\n");

	err = brcmf_debug_create_memdump(ifp->drvr->bus_if, data,
					 evtmsg->datalen);
	if (err)
		bphy_err(drvr, "Failed to get memory dump, %d\n", err);

	return err;
}