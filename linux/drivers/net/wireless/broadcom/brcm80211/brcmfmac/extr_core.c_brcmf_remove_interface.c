#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct brcmf_if {size_t bsscfgidx; TYPE_1__* drvr; int /*<<< orphan*/  ifidx; } ;
struct TYPE_3__ {struct brcmf_if** iflist; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_del_if (TYPE_1__*,size_t,int) ; 
 int /*<<< orphan*/  brcmf_proto_del_if (TYPE_1__*,struct brcmf_if*) ; 

void brcmf_remove_interface(struct brcmf_if *ifp, bool rtnl_locked)
{
	if (!ifp || WARN_ON(ifp->drvr->iflist[ifp->bsscfgidx] != ifp))
		return;
	brcmf_dbg(TRACE, "Enter, bsscfgidx=%d, ifidx=%d\n", ifp->bsscfgidx,
		  ifp->ifidx);
	brcmf_proto_del_if(ifp->drvr, ifp);
	brcmf_del_if(ifp->drvr, ifp->bsscfgidx, rtnl_locked);
}