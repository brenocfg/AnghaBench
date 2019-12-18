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
typedef  int /*<<< orphan*/  u16 ;
struct wlandevice {struct hfa384x* priv; } ;
struct net_device {int flags; } ;
struct hfa384x {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384x_RID_PROMISCMODE ; 
 scalar_t__ HFA384x_STATE_RUNNING ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  P80211ENUM_truth_false ; 
 int /*<<< orphan*/  P80211ENUM_truth_true ; 
 int hfa384x_drvr_setconfig16_async (struct hfa384x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prism2sta_setmulticast(struct wlandevice *wlandev,
				  struct net_device *dev)
{
	int result = 0;
	struct hfa384x *hw = wlandev->priv;

	u16 promisc;

	/* If we're not ready, what's the point? */
	if (hw->state != HFA384x_STATE_RUNNING)
		goto exit;

	if ((dev->flags & (IFF_PROMISC | IFF_ALLMULTI)) != 0)
		promisc = P80211ENUM_truth_true;
	else
		promisc = P80211ENUM_truth_false;

	result =
	    hfa384x_drvr_setconfig16_async(hw, HFA384x_RID_PROMISCMODE,
					   promisc);
exit:
	return result;
}