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
struct usbnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_80211_INFRA_INFRA ; 
 int /*<<< orphan*/  NL80211_AUTHTYPE_OPEN_SYSTEM ; 
 int /*<<< orphan*/  RNDIS_WLAN_ALG_NONE ; 
 int /*<<< orphan*/  RNDIS_WLAN_KEY_MGMT_NONE ; 
 int /*<<< orphan*/  set_auth_mode (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_encr_mode (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_infra_mode (struct usbnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_priv_filter (struct usbnet*) ; 

__attribute__((used)) static void set_default_iw_params(struct usbnet *usbdev)
{
	set_infra_mode(usbdev, NDIS_80211_INFRA_INFRA);
	set_auth_mode(usbdev, 0, NL80211_AUTHTYPE_OPEN_SYSTEM,
						RNDIS_WLAN_KEY_MGMT_NONE);
	set_priv_filter(usbdev);
	set_encr_mode(usbdev, RNDIS_WLAN_ALG_NONE, RNDIS_WLAN_ALG_NONE);
}