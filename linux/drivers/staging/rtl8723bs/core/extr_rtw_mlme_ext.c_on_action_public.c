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
struct TYPE_3__ {scalar_t__* rx_data; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  scalar_t__ u8 ;
struct ieee80211_hdr_3addr {int dummy; } ;
struct adapter {int /*<<< orphan*/  eeprompriv; } ;

/* Variables and functions */
#define  ACT_PUBLIC_VENDOR 128 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GetAddr1Ptr (scalar_t__*) ; 
 scalar_t__ RTW_WLAN_CATEGORY_PUBLIC ; 
 unsigned int _FAIL ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  myid (int /*<<< orphan*/ *) ; 
 unsigned int on_action_public_default (union recv_frame*,scalar_t__) ; 
 unsigned int on_action_public_vendor (union recv_frame*) ; 

unsigned int on_action_public(struct adapter *padapter, union recv_frame *precv_frame)
{
	unsigned int ret = _FAIL;
	u8 *pframe = precv_frame->u.hdr.rx_data;
	u8 *frame_body = pframe + sizeof(struct ieee80211_hdr_3addr);
	u8 category, action;

	/* check RA matches or not */
	if (memcmp(myid(&(padapter->eeprompriv)), GetAddr1Ptr(pframe), ETH_ALEN))
		goto exit;

	category = frame_body[0];
	if (category != RTW_WLAN_CATEGORY_PUBLIC)
		goto exit;

	action = frame_body[1];
	switch (action) {
	case ACT_PUBLIC_VENDOR:
		ret = on_action_public_vendor(precv_frame);
		break;
	default:
		ret = on_action_public_default(precv_frame, action);
		break;
	}

exit:
	return ret;
}