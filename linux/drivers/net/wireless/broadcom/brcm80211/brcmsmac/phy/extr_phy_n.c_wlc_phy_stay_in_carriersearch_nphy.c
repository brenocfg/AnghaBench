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
typedef  int u16 ;
struct brcms_phy {scalar_t__ nphy_deaf_count; int classifier_state; int* clip_state; } ;

/* Variables and functions */
 int wlc_phy_classifier_nphy (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  wlc_phy_clip_det_nphy (struct brcms_phy*,int,int*) ; 
 int /*<<< orphan*/  wlc_phy_resetcca_nphy (struct brcms_phy*) ; 

void wlc_phy_stay_in_carriersearch_nphy(struct brcms_phy *pi, bool enable)
{
	u16 clip_off[] = { 0xffff, 0xffff };

	if (enable) {
		if (pi->nphy_deaf_count == 0) {
			pi->classifier_state =
				wlc_phy_classifier_nphy(pi, 0, 0);
			wlc_phy_classifier_nphy(pi, (0x7 << 0), 4);
			wlc_phy_clip_det_nphy(pi, 0, pi->clip_state);
			wlc_phy_clip_det_nphy(pi, 1, clip_off);
		}

		pi->nphy_deaf_count++;

		wlc_phy_resetcca_nphy(pi);

	} else {
		pi->nphy_deaf_count--;

		if (pi->nphy_deaf_count == 0) {
			wlc_phy_classifier_nphy(pi, (0x7 << 0),
						pi->classifier_state);
			wlc_phy_clip_det_nphy(pi, 1, pi->clip_state);
		}
	}
}