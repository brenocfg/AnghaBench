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
struct brcmf_p2p_info {TYPE_1__* bss_idx; } ;
struct brcmf_cfg80211_vif {int /*<<< orphan*/  ifp; } ;
struct TYPE_2__ {struct brcmf_cfg80211_vif* vif; } ;

/* Variables and functions */
 size_t P2PAPI_BSSCFG_DEVICE ; 
 int /*<<< orphan*/  brcmf_p2p_cancel_remain_on_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_p2p_deinit_discovery (struct brcmf_p2p_info*) ; 
 int /*<<< orphan*/  brcmf_remove_interface (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct brcmf_p2p_info*,int /*<<< orphan*/ ,int) ; 

void brcmf_p2p_detach(struct brcmf_p2p_info *p2p)
{
	struct brcmf_cfg80211_vif *vif;

	vif = p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vif;
	if (vif != NULL) {
		brcmf_p2p_cancel_remain_on_channel(vif->ifp);
		brcmf_p2p_deinit_discovery(p2p);
		brcmf_remove_interface(vif->ifp, false);
	}
	/* just set it all to zero */
	memset(p2p, 0, sizeof(*p2p));
}