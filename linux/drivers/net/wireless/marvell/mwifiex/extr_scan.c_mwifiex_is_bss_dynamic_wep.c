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
struct TYPE_2__ {scalar_t__ encryption_mode; int /*<<< orphan*/  wpa2_enabled; int /*<<< orphan*/  wpa_enabled; int /*<<< orphan*/  wep_enabled; } ;
struct mwifiex_private {TYPE_1__ sec_info; } ;
struct mwifiex_bssdescriptor {scalar_t__ privacy; int /*<<< orphan*/  bcn_rsn_ie; int /*<<< orphan*/  bcn_wpa_ie; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  WLAN_EID_RSN ; 
 int /*<<< orphan*/  WLAN_EID_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  dbg_security_flags (int /*<<< orphan*/ ,char*,struct mwifiex_private*,struct mwifiex_bssdescriptor*) ; 
 int /*<<< orphan*/  has_ieee_hdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  has_vendor_hdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
mwifiex_is_bss_dynamic_wep(struct mwifiex_private *priv,
			   struct mwifiex_bssdescriptor *bss_desc)
{
	if (!priv->sec_info.wep_enabled && !priv->sec_info.wpa_enabled &&
	    !priv->sec_info.wpa2_enabled &&
	    !has_vendor_hdr(bss_desc->bcn_wpa_ie, WLAN_EID_VENDOR_SPECIFIC) &&
	    !has_ieee_hdr(bss_desc->bcn_rsn_ie, WLAN_EID_RSN) &&
	    priv->sec_info.encryption_mode && bss_desc->privacy) {
		dbg_security_flags(INFO, "dynamic", priv, bss_desc);
		return true;
	}
	return false;
}