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
typedef  int u32 ;
struct wlandevice {int /*<<< orphan*/  netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct p80211msg_dot11req_mibset {TYPE_1__ resultcode; } ;
struct mibrec {int dummy; } ;
struct hfa384x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P80211ENUM_resultcode_not_supported ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int prism2mib_uint32 (struct mibrec*,int,struct wlandevice*,struct hfa384x*,struct p80211msg_dot11req_mibset*,void*) ; 

__attribute__((used)) static int
prism2mib_fragmentationthreshold(struct mibrec *mib,
				 int isget,
				 struct wlandevice *wlandev,
				 struct hfa384x *hw,
				 struct p80211msg_dot11req_mibset *msg,
				 void *data)
{
	u32 *uint32 = data;

	if (!isget)
		if ((*uint32) % 2) {
			netdev_warn(wlandev->netdev,
				    "Attempt to set odd number FragmentationThreshold\n");
			msg->resultcode.data =
			    P80211ENUM_resultcode_not_supported;
			return 0;
		}

	return prism2mib_uint32(mib, isget, wlandev, hw, msg, data);
}