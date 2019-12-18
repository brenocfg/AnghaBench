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
struct wlandevice {int hostwep; } ;
struct p80211msg_dot11req_mibset {int dummy; } ;
struct mibrec {int /*<<< orphan*/  parm2; } ;
struct hfa384x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384x_WEPFLAGS_DISABLE_RXCRYPT ; 
 int /*<<< orphan*/  HFA384x_WEPFLAGS_DISABLE_TXCRYPT ; 
 int HOSTWEP_DECRYPT ; 
 int HOSTWEP_ENCRYPT ; 
 int prism2mib_flag (struct mibrec*,int,struct wlandevice*,struct hfa384x*,struct p80211msg_dot11req_mibset*,void*) ; 

__attribute__((used)) static int prism2mib_privacyinvoked(struct mibrec *mib,
				    int isget,
				    struct wlandevice *wlandev,
				    struct hfa384x *hw,
				    struct p80211msg_dot11req_mibset *msg,
				    void *data)
{
	if (wlandev->hostwep & HOSTWEP_DECRYPT) {
		if (wlandev->hostwep & HOSTWEP_DECRYPT)
			mib->parm2 |= HFA384x_WEPFLAGS_DISABLE_RXCRYPT;
		if (wlandev->hostwep & HOSTWEP_ENCRYPT)
			mib->parm2 |= HFA384x_WEPFLAGS_DISABLE_TXCRYPT;
	}

	return prism2mib_flag(mib, isget, wlandev, hw, msg, data);
}