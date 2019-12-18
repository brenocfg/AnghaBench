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
struct TYPE_3__ {int /*<<< orphan*/ * pkt; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
struct recv_priv {scalar_t__ precv_frame_buf; } ;
typedef  scalar_t__ sint ;

/* Variables and functions */
 scalar_t__ NR_RECVFRAME ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 

void rtw_os_recv_resource_free(struct recv_priv *precvpriv)
{
	sint i;
	union recv_frame *precvframe;

	precvframe = (union recv_frame*) precvpriv->precv_frame_buf;

	for (i = 0; i < NR_RECVFRAME; i++) {
		if (precvframe->u.hdr.pkt) {
			dev_kfree_skb_any(precvframe->u.hdr.pkt);/* free skb by driver */
			precvframe->u.hdr.pkt = NULL;
		}
		precvframe++;
	}
}