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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wlandevice {int dummy; } ;
struct wiphy {int dummy; } ;
struct net_device {struct wlandevice* ml_priv; } ;
struct key_params {scalar_t__ cipher; int /*<<< orphan*/  key; int /*<<< orphan*/  key_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIDMIB_DOT11SMT_PRIVACYTABLE_WEPDEFAULTKEYID ; 
 int EFAULT ; 
 int EINVAL ; 
 scalar_t__ NUM_WEPKEYS ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP104 ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP40 ; 
 int /*<<< orphan*/  didmib_dot11smt_wepdefaultkeystable_key (scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ prism2_domibset_pstr32 (struct wlandevice*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ prism2_domibset_uint32 (struct wlandevice*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int prism2_add_key(struct wiphy *wiphy, struct net_device *dev,
			  u8 key_index, bool pairwise, const u8 *mac_addr,
			  struct key_params *params)
{
	struct wlandevice *wlandev = dev->ml_priv;
	u32 did;

	if (key_index >= NUM_WEPKEYS)
		return -EINVAL;

	if (params->cipher != WLAN_CIPHER_SUITE_WEP40 &&
	    params->cipher != WLAN_CIPHER_SUITE_WEP104) {
		pr_debug("Unsupported cipher suite\n");
		return -EFAULT;
	}

	if (prism2_domibset_uint32(wlandev,
				   DIDMIB_DOT11SMT_PRIVACYTABLE_WEPDEFAULTKEYID,
				   key_index))
		return -EFAULT;

	/* send key to driver */
	did = didmib_dot11smt_wepdefaultkeystable_key(key_index + 1);

	if (prism2_domibset_pstr32(wlandev, did, params->key_len, params->key))
		return -EFAULT;
	return 0;
}