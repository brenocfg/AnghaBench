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
typedef  int /*<<< orphan*/  u8 ;
struct brcms_c_info {TYPE_1__* bsscfg; int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  BSSID; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int RCM_BSSID_OFFSET ; 
 int /*<<< orphan*/  brcms_b_set_addrmatch (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

void
brcms_c_set_addrmatch(struct brcms_c_info *wlc, int match_reg_offset,
		  const u8 *addr)
{
	brcms_b_set_addrmatch(wlc->hw, match_reg_offset, addr);
	if (match_reg_offset == RCM_BSSID_OFFSET)
		memcpy(wlc->bsscfg->BSSID, addr, ETH_ALEN);
}