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
struct qtnf_wmac {struct qtnf_vif* iflist; } ;
struct TYPE_2__ {scalar_t__ iftype; } ;
struct qtnf_vif {TYPE_1__ wdev; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_UNSPECIFIED ; 
 int QTNF_MAX_INTF ; 

struct qtnf_vif *qtnf_mac_get_free_vif(struct qtnf_wmac *mac)
{
	struct qtnf_vif *vif;
	int i;

	for (i = 0; i < QTNF_MAX_INTF; i++) {
		vif = &mac->iflist[i];
		if (vif->wdev.iftype == NL80211_IFTYPE_UNSPECIFIED)
			return vif;
	}

	return NULL;
}