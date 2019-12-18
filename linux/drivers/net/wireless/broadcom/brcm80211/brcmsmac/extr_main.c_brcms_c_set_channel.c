#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct brcms_c_info {int bandinit_pending; TYPE_3__* band; TYPE_2__* pub; TYPE_1__* default_bss; int /*<<< orphan*/  cmi; } ;
struct TYPE_6__ {scalar_t__ bandunit; int /*<<< orphan*/  pi; } ;
struct TYPE_5__ {scalar_t__ up; } ;
struct TYPE_4__ {scalar_t__ chanspec; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MAXCHANNEL ; 
 int /*<<< orphan*/  brcms_c_enable_mac (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_set_chanspec (struct brcms_c_info*,scalar_t__) ; 
 int /*<<< orphan*/  brcms_c_set_home_chanspec (struct brcms_c_info*,scalar_t__) ; 
 int /*<<< orphan*/  brcms_c_suspend_mac_and_wait (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_valid_chanspec_db (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ brcms_is_mband_unlocked (struct brcms_c_info*) ; 
 scalar_t__ ch20mhz_chspec (scalar_t__) ; 
 scalar_t__ chspec_bandunit (scalar_t__) ; 
 scalar_t__ wlc_phy_chanspec_get (int /*<<< orphan*/ ) ; 

int brcms_c_set_channel(struct brcms_c_info *wlc, u16 channel)
{
	u16 chspec = ch20mhz_chspec(channel);

	if (channel < 0 || channel > MAXCHANNEL)
		return -EINVAL;

	if (!brcms_c_valid_chanspec_db(wlc->cmi, chspec))
		return -EINVAL;


	if (!wlc->pub->up && brcms_is_mband_unlocked(wlc)) {
		if (wlc->band->bandunit != chspec_bandunit(chspec))
			wlc->bandinit_pending = true;
		else
			wlc->bandinit_pending = false;
	}

	wlc->default_bss->chanspec = chspec;
	/* brcms_c_BSSinit() will sanitize the rateset before
	 * using it.. */
	if (wlc->pub->up && (wlc_phy_chanspec_get(wlc->band->pi) != chspec)) {
		brcms_c_set_home_chanspec(wlc, chspec);
		brcms_c_suspend_mac_and_wait(wlc);
		brcms_c_set_chanspec(wlc, chspec);
		brcms_c_enable_mac(wlc);
	}
	return 0;
}