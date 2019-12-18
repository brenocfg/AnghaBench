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
typedef  int /*<<< orphan*/  u8 ;
struct brcmf_pub {int dummy; } ;
struct brcmf_pno_bssid_le {scalar_t__ flags; int /*<<< orphan*/  bssid; } ;
struct brcmf_if {struct brcmf_pub* drvr; } ;
typedef  int /*<<< orphan*/  bssid_cfg ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  SCAN ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,int) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int brcmf_fil_iovar_data_set (struct brcmf_if*,char*,struct brcmf_pno_bssid_le*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_pno_add_bssid(struct brcmf_if *ifp, const u8 *bssid)
{
	struct brcmf_pub *drvr = ifp->drvr;
	struct brcmf_pno_bssid_le bssid_cfg;
	int err;

	memcpy(bssid_cfg.bssid, bssid, ETH_ALEN);
	bssid_cfg.flags = 0;

	brcmf_dbg(SCAN, "adding bssid=%pM\n", bssid);
	err = brcmf_fil_iovar_data_set(ifp, "pfn_add_bssid", &bssid_cfg,
				       sizeof(bssid_cfg));
	if (err < 0)
		bphy_err(drvr, "adding failed: err=%d\n", err);
	return err;
}