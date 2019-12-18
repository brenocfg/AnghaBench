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
struct brcms_c_info {int /*<<< orphan*/  probe_resp; TYPE_1__* pub; struct brcms_bss_cfg* bsscfg; } ;
struct brcms_bss_cfg {scalar_t__ type; } ;
struct TYPE_2__ {scalar_t__ up; } ;

/* Variables and functions */
 scalar_t__ BRCMS_TYPE_ADHOC ; 
 scalar_t__ BRCMS_TYPE_AP ; 
 int /*<<< orphan*/  brcms_c_bss_update_probe_resp (struct brcms_c_info*,struct brcms_bss_cfg*,int /*<<< orphan*/ ,int) ; 

void brcms_c_update_probe_resp(struct brcms_c_info *wlc, bool suspend)
{
	struct brcms_bss_cfg *bsscfg = wlc->bsscfg;

	/* update AP or IBSS probe responses */
	if (wlc->pub->up && (bsscfg->type == BRCMS_TYPE_AP ||
			     bsscfg->type == BRCMS_TYPE_ADHOC)) {
		if (!wlc->probe_resp)
			return;
		brcms_c_bss_update_probe_resp(wlc, bsscfg, wlc->probe_resp,
					      suspend);
	}
}