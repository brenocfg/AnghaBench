#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wlandevice {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct p80211msg_dot11req_mibset {int /*<<< orphan*/  msgcode; TYPE_1__ mibattribute; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct p80211item_pstr32 {TYPE_2__ data; int /*<<< orphan*/  did; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIDMSG_DOT11REQ_MIBSET ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int p80211req_dorequest (struct wlandevice*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int prism2_domibset_pstr32(struct wlandevice *wlandev,
				  u32 did, u8 len, const u8 *data)
{
	struct p80211msg_dot11req_mibset msg;
	struct p80211item_pstr32 *mibitem =
			(struct p80211item_pstr32 *)&msg.mibattribute.data;

	msg.msgcode = DIDMSG_DOT11REQ_MIBSET;
	mibitem->did = did;
	mibitem->data.len = len;
	memcpy(mibitem->data.data, data, len);

	return p80211req_dorequest(wlandev, (u8 *)&msg);
}