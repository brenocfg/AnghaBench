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
typedef  int /*<<< orphan*/  u8 ;
struct wilc_vif {int dummy; } ;
struct wilc_pmkid_attr {int numpmkid; } ;
struct wilc_pmkid {int dummy; } ;
struct wid {int size; int /*<<< orphan*/ * val; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  WID_PMKID_INFO ; 
 int /*<<< orphan*/  WID_STR ; 
 int /*<<< orphan*/  WILC_SET_CFG ; 
 int wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,int) ; 

int wilc_set_pmkid_info(struct wilc_vif *vif, struct wilc_pmkid_attr *pmkid)
{
	struct wid wid;

	wid.id = WID_PMKID_INFO;
	wid.type = WID_STR;
	wid.size = (pmkid->numpmkid * sizeof(struct wilc_pmkid)) + 1;
	wid.val = (u8 *)pmkid;

	return wilc_send_config_pkt(vif, WILC_SET_CFG, &wid, 1);
}