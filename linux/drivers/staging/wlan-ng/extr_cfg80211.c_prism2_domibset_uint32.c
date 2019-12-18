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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
struct wlandevice {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct p80211msg_dot11req_mibset {int /*<<< orphan*/  msgcode; TYPE_1__ mibattribute; } ;
struct p80211item_uint32 {void* data; void* did; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIDMSG_DOT11REQ_MIBSET ; 
 int p80211req_dorequest (struct wlandevice*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int prism2_domibset_uint32(struct wlandevice *wlandev,
				  u32 did, u32 data)
{
	struct p80211msg_dot11req_mibset msg;
	struct p80211item_uint32 *mibitem =
			(struct p80211item_uint32 *)&msg.mibattribute.data;

	msg.msgcode = DIDMSG_DOT11REQ_MIBSET;
	mibitem->did = did;
	mibitem->data = data;

	return p80211req_dorequest(wlandev, (u8 *)&msg);
}