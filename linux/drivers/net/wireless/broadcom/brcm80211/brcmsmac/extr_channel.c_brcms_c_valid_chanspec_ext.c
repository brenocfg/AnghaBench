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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct brcms_cm_info {struct brcms_c_info* wlc; } ;
struct brcms_c_info {TYPE_2__* pub; TYPE_1__* hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  unit; } ;
struct TYPE_3__ {int /*<<< orphan*/  d11core; } ;

/* Variables and functions */
 scalar_t__ CHANNEL_BANDUNIT (struct brcms_c_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHSPEC_CHANNEL (int /*<<< orphan*/ ) ; 
 scalar_t__ brcms_c_chspec_malformed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ chspec_bandunit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
brcms_c_valid_chanspec_ext(struct brcms_cm_info *wlc_cm, u16 chspec)
{
	struct brcms_c_info *wlc = wlc_cm->wlc;
	u8 channel = CHSPEC_CHANNEL(chspec);

	/* check the chanspec */
	if (brcms_c_chspec_malformed(chspec)) {
		brcms_err(wlc->hw->d11core, "wl%d: malformed chanspec 0x%x\n",
			  wlc->pub->unit, chspec);
		return false;
	}

	if (CHANNEL_BANDUNIT(wlc_cm->wlc, channel) !=
	    chspec_bandunit(chspec))
		return false;

	return true;
}