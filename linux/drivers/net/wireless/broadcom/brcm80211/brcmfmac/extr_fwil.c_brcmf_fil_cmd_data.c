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
typedef  int /*<<< orphan*/  u32 ;
struct brcmf_pub {TYPE_1__* bus_if; } ;
struct brcmf_if {scalar_t__ fwil_fwerr; int /*<<< orphan*/  ifidx; struct brcmf_pub* drvr; } ;
typedef  int s32 ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ BRCMF_BUS_UP ; 
 int /*<<< orphan*/  BRCMF_DCMD_MAXLEN ; 
 int EBADE ; 
 int EIO ; 
 int /*<<< orphan*/  FIL ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  brcmf_fil_get_errstr (int /*<<< orphan*/ ) ; 
 int brcmf_proto_query_dcmd (struct brcmf_pub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int*) ; 
 int brcmf_proto_set_dcmd (struct brcmf_pub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uint ; 

__attribute__((used)) static s32
brcmf_fil_cmd_data(struct brcmf_if *ifp, u32 cmd, void *data, u32 len, bool set)
{
	struct brcmf_pub *drvr = ifp->drvr;
	s32 err, fwerr;

	if (drvr->bus_if->state != BRCMF_BUS_UP) {
		bphy_err(drvr, "bus is down. we have nothing to do.\n");
		return -EIO;
	}

	if (data != NULL)
		len = min_t(uint, len, BRCMF_DCMD_MAXLEN);
	if (set)
		err = brcmf_proto_set_dcmd(drvr, ifp->ifidx, cmd,
					   data, len, &fwerr);
	else
		err = brcmf_proto_query_dcmd(drvr, ifp->ifidx, cmd,
					     data, len, &fwerr);

	if (err) {
		brcmf_dbg(FIL, "Failed: error=%d\n", err);
	} else if (fwerr < 0) {
		brcmf_dbg(FIL, "Firmware error: %s (%d)\n",
			  brcmf_fil_get_errstr((u32)(-fwerr)), fwerr);
		err = -EBADE;
	}
	if (ifp->fwil_fwerr)
		return fwerr;

	return err;
}