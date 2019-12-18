#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ rx_data; scalar_t__ rx_tail; struct _adapter* adapter; } ;
struct TYPE_7__ {TYPE_2__ hdr; } ;
union recv_frame {TYPE_3__ u; } ;
typedef  scalar_t__ uint ;
struct recv_priv {scalar_t__ rx_drop; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_pkts; } ;
struct TYPE_8__ {scalar_t__ rx_pktloss; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* LedControlHandler ) (struct _adapter*,int /*<<< orphan*/ ) ;} ;
struct _adapter {TYPE_4__ mppriv; TYPE_1__ ledpriv; struct recv_priv recvpriv; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  LED_CTL_RX ; 
 scalar_t__ _FAIL ; 
 scalar_t__ _SUCCESS ; 
 scalar_t__ recv_func (struct _adapter*,union recv_frame*) ; 
 int /*<<< orphan*/  stub1 (struct _adapter*,int /*<<< orphan*/ ) ; 

void r8712_recv_entry(union recv_frame *precvframe)
{
	struct _adapter *padapter;
	struct recv_priv *precvpriv;

	s32 ret = _SUCCESS;

	padapter = precvframe->u.hdr.adapter;
	precvpriv = &(padapter->recvpriv);

	padapter->ledpriv.LedControlHandler(padapter, LED_CTL_RX);

	ret = recv_func(padapter, precvframe);
	if (ret == _FAIL)
		goto _recv_entry_drop;
	precvpriv->rx_pkts++;
	precvpriv->rx_bytes += (uint)(precvframe->u.hdr.rx_tail -
				precvframe->u.hdr.rx_data);
	return;
_recv_entry_drop:
	precvpriv->rx_drop++;
	padapter->mppriv.rx_pktloss = precvpriv->rx_drop;
}