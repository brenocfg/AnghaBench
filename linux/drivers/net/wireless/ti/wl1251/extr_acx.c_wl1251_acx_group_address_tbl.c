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
typedef  int u32 ;
struct wl1251 {int dummy; } ;
struct acx_dot11_grp_addr_tbl {int enabled; int num_groups; int /*<<< orphan*/  mac_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ACX ; 
 int /*<<< orphan*/  DOT11_GROUP_ADDRESS_TBL ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_dot11_grp_addr_tbl*) ; 
 struct acx_dot11_grp_addr_tbl* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_dot11_grp_addr_tbl*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_group_address_tbl(struct wl1251 *wl, bool enable,
				 void *mc_list, u32 mc_list_len)
{
	struct acx_dot11_grp_addr_tbl *acx;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx group address tbl");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx)
		return -ENOMEM;

	/* MAC filtering */
	acx->enabled = enable;
	acx->num_groups = mc_list_len;
	memcpy(acx->mac_table, mc_list, mc_list_len * ETH_ALEN);

	ret = wl1251_cmd_configure(wl, DOT11_GROUP_ADDRESS_TBL,
				   acx, sizeof(*acx));
	if (ret < 0) {
		wl1251_warning("failed to set group addr table: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}