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
struct brcms_c_info {scalar_t__ home_chanspec; TYPE_3__* bsscfg; TYPE_1__* pub; } ;
struct TYPE_6__ {TYPE_2__* current_bss; } ;
struct TYPE_5__ {scalar_t__ chanspec; } ;
struct TYPE_4__ {scalar_t__ associated; } ;

/* Variables and functions */

__attribute__((used)) static void brcms_c_set_home_chanspec(struct brcms_c_info *wlc, u16 chanspec)
{
	if (wlc->home_chanspec != chanspec) {
		wlc->home_chanspec = chanspec;

		if (wlc->pub->associated)
			wlc->bsscfg->current_bss->chanspec = chanspec;
	}
}