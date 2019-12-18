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
struct wlandevice {struct hfa384x* priv; } ;
struct hfa384x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384x_RID_CNFMAXDATALEN ; 
 int /*<<< orphan*/  WLAN_DATA_MAXLEN ; 
 int hfa384x_drvr_setconfig16 (struct hfa384x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prism2sta_globalsetup(struct wlandevice *wlandev)
{
	struct hfa384x *hw = wlandev->priv;

	/* Set the maximum frame size */
	return hfa384x_drvr_setconfig16(hw, HFA384x_RID_CNFMAXDATALEN,
					WLAN_DATA_MAXLEN);
}