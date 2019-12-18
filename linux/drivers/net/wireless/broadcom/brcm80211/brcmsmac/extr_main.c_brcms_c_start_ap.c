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
typedef  int /*<<< orphan*/  const u8 ;
struct brcms_c_info {int /*<<< orphan*/  hw; TYPE_2__* bsscfg; TYPE_1__* pub; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/  BSSID; } ;
struct TYPE_3__ {int /*<<< orphan*/  cur_etheraddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMS_TYPE_AP ; 
 int MCTL_AP ; 
 int MCTL_INFRA ; 
 int /*<<< orphan*/  brcms_b_mctrl (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  brcms_c_set_ssid (struct brcms_c_info*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

void brcms_c_start_ap(struct brcms_c_info *wlc, u8 *addr, const u8 *bssid,
		      u8 *ssid, size_t ssid_len)
{
	brcms_c_set_ssid(wlc, ssid, ssid_len);

	memcpy(wlc->pub->cur_etheraddr, addr, sizeof(wlc->pub->cur_etheraddr));
	memcpy(wlc->bsscfg->BSSID, bssid, sizeof(wlc->bsscfg->BSSID));
	wlc->bsscfg->type = BRCMS_TYPE_AP;

	brcms_b_mctrl(wlc->hw, MCTL_AP | MCTL_INFRA, MCTL_AP | MCTL_INFRA);
}