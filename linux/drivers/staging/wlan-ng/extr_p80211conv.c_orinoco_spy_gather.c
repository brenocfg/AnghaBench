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
struct wlandevice {int spy_number; TYPE_1__* spy_stat; int /*<<< orphan*/ * spy_address; } ;
struct p80211_rxmeta {scalar_t__ signal; scalar_t__ noise; } ;
struct TYPE_2__ {scalar_t__ level; scalar_t__ noise; scalar_t__ qual; int updated; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void orinoco_spy_gather(struct wlandevice *wlandev, char *mac,
			       struct p80211_rxmeta *rxmeta)
{
	int i;

	/* Gather wireless spy statistics: for each packet, compare the
	 * source address with out list, and if match, get the stats...
	 */

	for (i = 0; i < wlandev->spy_number; i++) {
		if (!memcmp(wlandev->spy_address[i], mac, ETH_ALEN)) {
			wlandev->spy_stat[i].level = rxmeta->signal;
			wlandev->spy_stat[i].noise = rxmeta->noise;
			wlandev->spy_stat[i].qual =
			    (rxmeta->signal >
			     rxmeta->noise) ? (rxmeta->signal -
					       rxmeta->noise) : 0;
			wlandev->spy_stat[i].updated = 0x7;
		}
	}
}