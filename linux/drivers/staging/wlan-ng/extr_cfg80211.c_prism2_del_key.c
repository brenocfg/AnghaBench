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

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 scalar_t__ NUM_WEPKEYS ; 
 int /*<<< orphan*/  didmib_dot11smt_wepdefaultkeystable_key (scalar_t__) ; 
 int prism2_domibset_pstr32 (struct wlandevice*,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int prism2_del_key(struct wiphy *wiphy, struct net_device *dev,
			  u8 key_index, bool pairwise, const u8 *mac_addr)
{
	struct wlandevice *wlandev = dev->ml_priv;
	u32 did;
	int err = 0;
	int result = 0;

	/* There is no direct way in the hardware (AFAIK) of removing
	 * a key, so we will cheat by setting the key to a bogus value
	 */

	if (key_index >= NUM_WEPKEYS)
		return -EINVAL;

	/* send key to driver */
	did = didmib_dot11smt_wepdefaultkeystable_key(key_index + 1);
	result = prism2_domibset_pstr32(wlandev, did, 13, "0000000000000");

	if (result)
		err = -EFAULT;

	return err;
}