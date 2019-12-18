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
struct recv_frame {TYPE_1__* pkt; } ;
struct ieee80211_hdr_3addr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_OUI ; 
 unsigned int _FAIL ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 unsigned int on_action_public_p2p (struct recv_frame*) ; 

__attribute__((used)) static unsigned int on_action_public_vendor(struct recv_frame *precv_frame)
{
	unsigned int ret = _FAIL;
	u8 *pframe = precv_frame->pkt->data;
	u8 *frame_body = pframe + sizeof(struct ieee80211_hdr_3addr);

	if (!memcmp(frame_body + 2, P2P_OUI, 4))
		ret = on_action_public_p2p(precv_frame);

	return ret;
}