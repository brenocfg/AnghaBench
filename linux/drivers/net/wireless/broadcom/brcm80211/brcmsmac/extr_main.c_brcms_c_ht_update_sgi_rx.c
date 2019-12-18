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
struct brcms_c_info {TYPE_1__* pub; } ;
struct TYPE_2__ {scalar_t__ up; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_c_update_beacon (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_update_probe_resp (struct brcms_c_info*,int) ; 

__attribute__((used)) static void brcms_c_ht_update_sgi_rx(struct brcms_c_info *wlc, int val)
{
	if (wlc->pub->up) {
		brcms_c_update_beacon(wlc);
		brcms_c_update_probe_resp(wlc, true);
	}
}