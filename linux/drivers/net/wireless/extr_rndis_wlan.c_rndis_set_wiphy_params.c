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
struct wiphy {int /*<<< orphan*/  rts_threshold; int /*<<< orphan*/  frag_threshold; } ;
struct usbnet {int dummy; } ;
struct rndis_wlan_private {struct usbnet* usbdev; } ;

/* Variables and functions */
 int WIPHY_PARAM_FRAG_THRESHOLD ; 
 int WIPHY_PARAM_RTS_THRESHOLD ; 
 int set_frag_threshold (struct usbnet*,int /*<<< orphan*/ ) ; 
 int set_rts_threshold (struct usbnet*,int /*<<< orphan*/ ) ; 
 struct rndis_wlan_private* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int rndis_set_wiphy_params(struct wiphy *wiphy, u32 changed)
{
	struct rndis_wlan_private *priv = wiphy_priv(wiphy);
	struct usbnet *usbdev = priv->usbdev;
	int err;

	if (changed & WIPHY_PARAM_FRAG_THRESHOLD) {
		err = set_frag_threshold(usbdev, wiphy->frag_threshold);
		if (err < 0)
			return err;
	}

	if (changed & WIPHY_PARAM_RTS_THRESHOLD) {
		err = set_rts_threshold(usbdev, wiphy->rts_threshold);
		if (err < 0)
			return err;
	}

	return 0;
}