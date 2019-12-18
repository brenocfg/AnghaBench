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
struct cfg80211_ssid {int ssid_len; int /*<<< orphan*/  ssid; } ;
struct brcmf_pub {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  SSID; void* SSID_len; } ;
struct brcmf_pno_net_param_le {TYPE_1__ ssid; void* flags; void* infra; void* wsec; void* wpa_auth; void* auth; } ;
struct brcmf_if {struct brcmf_pub* drvr; } ;
typedef  int /*<<< orphan*/  pfn ;

/* Variables and functions */
 int BRCMF_PNO_HIDDEN_BIT ; 
 int BRCMF_PNO_WPA_AUTH_ANY ; 
 int /*<<< orphan*/  SCAN ; 
 int WLAN_AUTH_OPEN ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,int) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int brcmf_fil_iovar_data_set (struct brcmf_if*,char*,struct brcmf_pno_net_param_le*,int) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int brcmf_pno_add_ssid(struct brcmf_if *ifp, struct cfg80211_ssid *ssid,
			      bool active)
{
	struct brcmf_pub *drvr = ifp->drvr;
	struct brcmf_pno_net_param_le pfn;
	int err;

	pfn.auth = cpu_to_le32(WLAN_AUTH_OPEN);
	pfn.wpa_auth = cpu_to_le32(BRCMF_PNO_WPA_AUTH_ANY);
	pfn.wsec = cpu_to_le32(0);
	pfn.infra = cpu_to_le32(1);
	pfn.flags = 0;
	if (active)
		pfn.flags = cpu_to_le32(1 << BRCMF_PNO_HIDDEN_BIT);
	pfn.ssid.SSID_len = cpu_to_le32(ssid->ssid_len);
	memcpy(pfn.ssid.SSID, ssid->ssid, ssid->ssid_len);

	brcmf_dbg(SCAN, "adding ssid=%.32s (active=%d)\n", ssid->ssid, active);
	err = brcmf_fil_iovar_data_set(ifp, "pfn_add", &pfn, sizeof(pfn));
	if (err < 0)
		bphy_err(drvr, "adding failed: err=%d\n", err);
	return err;
}