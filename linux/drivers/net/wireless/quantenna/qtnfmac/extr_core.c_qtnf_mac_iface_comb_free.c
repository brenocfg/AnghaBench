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
struct TYPE_2__ {int n_if_comb; struct ieee80211_iface_combination* if_comb; } ;
struct qtnf_wmac {TYPE_1__ macinfo; } ;
struct ieee80211_iface_combination {struct ieee80211_iface_combination* limits; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ieee80211_iface_combination*) ; 

void qtnf_mac_iface_comb_free(struct qtnf_wmac *mac)
{
	struct ieee80211_iface_combination *comb;
	int i;

	if (mac->macinfo.if_comb) {
		for (i = 0; i < mac->macinfo.n_if_comb; i++) {
			comb = &mac->macinfo.if_comb[i];
			kfree(comb->limits);
			comb->limits = NULL;
		}

		kfree(mac->macinfo.if_comb);
		mac->macinfo.if_comb = NULL;
	}
}