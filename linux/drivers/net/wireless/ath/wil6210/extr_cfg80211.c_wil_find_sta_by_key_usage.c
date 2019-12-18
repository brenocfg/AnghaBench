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
struct wil_sta_info {int dummy; } ;
struct wil6210_priv {struct wil_sta_info* sta; } ;
typedef  enum wmi_key_usage { ____Placeholder_wmi_key_usage } wmi_key_usage ;

/* Variables and functions */
 int EINVAL ; 
 struct wil_sta_info* ERR_PTR (int) ; 
 int WMI_KEY_USE_RX_GROUP ; 
 int WMI_KEY_USE_TX_GROUP ; 
 int /*<<< orphan*/ * key_usage_str ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int wil_find_cid (struct wil6210_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int wil_find_cid_by_idx (struct wil6210_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wil_sta_info *
wil_find_sta_by_key_usage(struct wil6210_priv *wil, u8 mid,
			  enum wmi_key_usage key_usage, const u8 *mac_addr)
{
	int cid = -EINVAL;

	if (key_usage == WMI_KEY_USE_TX_GROUP)
		return NULL; /* not needed */

	/* supplicant provides Rx group key in STA mode with NULL MAC address */
	if (mac_addr)
		cid = wil_find_cid(wil, mid, mac_addr);
	else if (key_usage == WMI_KEY_USE_RX_GROUP)
		cid = wil_find_cid_by_idx(wil, mid, 0);
	if (cid < 0) {
		wil_err(wil, "No CID for %pM %s\n", mac_addr,
			key_usage_str[key_usage]);
		return ERR_PTR(cid);
	}

	return &wil->sta[cid];
}