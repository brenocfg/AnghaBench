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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_bss_conf {int dummy; } ;
struct ar5523_cmd_rateset {int dummy; } ;
struct TYPE_2__ {void* wlanmode; int /*<<< orphan*/  rateset; } ;
struct ar5523_cmd_create_connection {TYPE_1__ connattr; void* size; void* bssid; void* connid; } ;
struct ar5523 {int dummy; } ;
typedef  int /*<<< orphan*/  create ;

/* Variables and functions */
 int /*<<< orphan*/  WDCMSG_CREATE_CONNECTION ; 
 int ar5523_cmd_write (struct ar5523*,int /*<<< orphan*/ ,struct ar5523_cmd_create_connection*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5523_create_rateset (struct ar5523*,struct ieee80211_bss_conf*,int /*<<< orphan*/ *,int) ; 
 int ar5523_get_wlan_mode (struct ar5523*,struct ieee80211_bss_conf*) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct ar5523_cmd_create_connection*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ar5523_create_connection(struct ar5523 *ar,
				    struct ieee80211_vif *vif,
				    struct ieee80211_bss_conf *bss)
{
	struct ar5523_cmd_create_connection create;
	int wlan_mode;

	memset(&create, 0, sizeof(create));
	create.connid = cpu_to_be32(2);
	create.bssid = cpu_to_be32(0);
	/* XXX packed or not?  */
	create.size = cpu_to_be32(sizeof(struct ar5523_cmd_rateset));

	ar5523_create_rateset(ar, bss, &create.connattr.rateset, false);

	wlan_mode = ar5523_get_wlan_mode(ar, bss);
	create.connattr.wlanmode = cpu_to_be32(wlan_mode);

	return ar5523_cmd_write(ar, WDCMSG_CREATE_CONNECTION, &create,
				sizeof(create), 0);
}