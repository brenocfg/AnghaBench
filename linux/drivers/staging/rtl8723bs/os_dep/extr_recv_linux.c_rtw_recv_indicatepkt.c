#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {int eth_type; } ;
struct TYPE_9__ {TYPE_4__* pkt; int /*<<< orphan*/  len; int /*<<< orphan*/  rx_data; int /*<<< orphan*/  rx_end; int /*<<< orphan*/  rx_tail; int /*<<< orphan*/  rx_head; struct rx_pkt_attrib attrib; } ;
struct TYPE_10__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
struct __queue {int dummy; } ;
struct recv_priv {struct __queue free_recv_queue; } ;
struct TYPE_11__ {int /*<<< orphan*/  os_indicate_err; int /*<<< orphan*/  os_indicate; } ;
struct adapter {TYPE_3__ rx_logs; struct recv_priv recvpriv; } ;
struct TYPE_12__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; int /*<<< orphan*/  head; } ;
typedef  TYPE_4__ _pkt ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_COUNTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_recv_osdep_c_ ; 
 int /*<<< orphan*/  rtw_free_recvframe (union recv_frame*,struct __queue*) ; 
 int /*<<< orphan*/  rtw_os_ksocket_send (struct adapter*,union recv_frame*) ; 
 int /*<<< orphan*/  rtw_os_recv_indicate_pkt (struct adapter*,TYPE_4__*,struct rx_pkt_attrib*) ; 
 int /*<<< orphan*/  skb_end_pointer (TYPE_4__*) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tail_pointer (TYPE_4__*) ; 

int rtw_recv_indicatepkt(struct adapter *padapter, union recv_frame *precv_frame)
{
	struct recv_priv *precvpriv;
	struct __queue	*pfree_recv_queue;
	_pkt *skb;
	struct rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;

	DBG_COUNTER(padapter->rx_logs.os_indicate);

	precvpriv = &(padapter->recvpriv);
	pfree_recv_queue = &(precvpriv->free_recv_queue);

	skb = precv_frame->u.hdr.pkt;
	if (skb == NULL) {
		RT_TRACE(_module_recv_osdep_c_, _drv_err_, ("rtw_recv_indicatepkt():skb == NULL something wrong!!!!\n"));
		goto _recv_indicatepkt_drop;
	}

	RT_TRACE(_module_recv_osdep_c_, _drv_info_, ("rtw_recv_indicatepkt():skb != NULL !!!\n"));
	RT_TRACE(_module_recv_osdep_c_, _drv_info_, ("rtw_recv_indicatepkt():precv_frame->u.hdr.rx_head =%p  precv_frame->hdr.rx_data =%p\n", precv_frame->u.hdr.rx_head, precv_frame->u.hdr.rx_data));
	RT_TRACE(_module_recv_osdep_c_, _drv_info_, ("precv_frame->hdr.rx_tail =%p precv_frame->u.hdr.rx_end =%p precv_frame->hdr.len =%d\n", precv_frame->u.hdr.rx_tail, precv_frame->u.hdr.rx_end, precv_frame->u.hdr.len));

	skb->data = precv_frame->u.hdr.rx_data;

	skb_set_tail_pointer(skb, precv_frame->u.hdr.len);

	skb->len = precv_frame->u.hdr.len;

	RT_TRACE(_module_recv_osdep_c_, _drv_info_, ("\n skb->head =%p skb->data =%p skb->tail =%p skb->end =%p skb->len =%d\n", skb->head, skb->data, skb_tail_pointer(skb), skb_end_pointer(skb), skb->len));

#ifdef CONFIG_AUTO_AP_MODE
	if (0x8899 == pattrib->eth_type) {
		rtw_os_ksocket_send(padapter, precv_frame);

		/* goto _recv_indicatepkt_drop; */
	}
#endif /* CONFIG_AUTO_AP_MODE */

	rtw_os_recv_indicate_pkt(padapter, skb, pattrib);

	precv_frame->u.hdr.pkt = NULL; /*  pointers to NULL before rtw_free_recvframe() */

	rtw_free_recvframe(precv_frame, pfree_recv_queue);

	RT_TRACE(_module_recv_osdep_c_, _drv_info_, ("\n rtw_recv_indicatepkt :after rtw_os_recv_indicate_pkt!!!!\n"));

	return _SUCCESS;

_recv_indicatepkt_drop:

	 /* enqueue back to free_recv_queue */
	 rtw_free_recvframe(precv_frame, pfree_recv_queue);

	 DBG_COUNTER(padapter->rx_logs.os_indicate_err);
	 return _FAIL;
}