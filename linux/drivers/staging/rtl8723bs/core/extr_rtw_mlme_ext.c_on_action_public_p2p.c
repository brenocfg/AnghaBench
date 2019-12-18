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
struct TYPE_3__ {unsigned char* rx_data; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  unsigned char u8 ;
struct ieee80211_hdr_3addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ _FAIL ; 
 unsigned int _SUCCESS ; 
 scalar_t__ rtw_action_public_decache (union recv_frame*,unsigned char) ; 

__attribute__((used)) static unsigned int on_action_public_p2p(union recv_frame *precv_frame)
{
	u8 *pframe = precv_frame->u.hdr.rx_data;
	u8 *frame_body;
	u8 dialogToken = 0;

	frame_body = (unsigned char *)(pframe + sizeof(struct ieee80211_hdr_3addr));

	dialogToken = frame_body[7];

	if (rtw_action_public_decache(precv_frame, dialogToken) == _FAIL)
		return _FAIL;

	return _SUCCESS;
}