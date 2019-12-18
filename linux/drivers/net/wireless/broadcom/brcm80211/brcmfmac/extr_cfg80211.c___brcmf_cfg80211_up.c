#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct brcmf_if {TYPE_2__* drvr; TYPE_1__* vif; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_4__ {int /*<<< orphan*/  config; } ;
struct TYPE_3__ {int /*<<< orphan*/  sme_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_VIF_STATUS_READY ; 
 int /*<<< orphan*/  brcmf_config_dongle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 __brcmf_cfg80211_up(struct brcmf_if *ifp)
{
	set_bit(BRCMF_VIF_STATUS_READY, &ifp->vif->sme_state);

	return brcmf_config_dongle(ifp->drvr->config);
}