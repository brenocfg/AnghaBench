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
struct brcms_c_info {TYPE_3__* band; TYPE_2__* pub; TYPE_1__* stf; } ;
typedef  scalar_t__ s8 ;
struct TYPE_6__ {int /*<<< orphan*/  pi; } ;
struct TYPE_5__ {scalar_t__ up; } ;
struct TYPE_4__ {scalar_t__ ldpc; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_c_update_beacon (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_update_probe_resp (struct brcms_c_info*,int) ; 
 int /*<<< orphan*/  wlc_phy_ldpc_override_set (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void brcms_c_ht_update_ldpc(struct brcms_c_info *wlc, s8 val)
{
	wlc->stf->ldpc = val;

	if (wlc->pub->up) {
		brcms_c_update_beacon(wlc);
		brcms_c_update_probe_resp(wlc, true);
		wlc_phy_ldpc_override_set(wlc->band->pi, (val ? true : false));
	}
}