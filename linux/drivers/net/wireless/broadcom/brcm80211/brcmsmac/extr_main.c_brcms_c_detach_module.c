#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct brcms_c_info {int /*<<< orphan*/ * ampdu; int /*<<< orphan*/ * asi; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_c_ampdu_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcms_c_antsel_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcms_c_stf_detach (struct brcms_c_info*) ; 

__attribute__((used)) static void brcms_c_detach_module(struct brcms_c_info *wlc)
{
	if (wlc->asi) {
		brcms_c_antsel_detach(wlc->asi);
		wlc->asi = NULL;
	}

	if (wlc->ampdu) {
		brcms_c_ampdu_detach(wlc->ampdu);
		wlc->ampdu = NULL;
	}

	brcms_c_stf_detach(wlc);
}