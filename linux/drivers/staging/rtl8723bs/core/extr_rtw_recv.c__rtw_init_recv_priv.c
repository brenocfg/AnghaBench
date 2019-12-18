#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct adapter* adapter; scalar_t__ len; } ;
struct TYPE_5__ {TYPE_1__ hdr; int /*<<< orphan*/  list; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int /*<<< orphan*/  queue; } ;
struct recv_priv {int free_recvframe_cnt; int signal_stat_sampling_interval; int /*<<< orphan*/  signal_stat_timer; TYPE_3__ free_recv_queue; int /*<<< orphan*/ * precv_frame_buf; scalar_t__ pallocated_frame_buf; struct adapter* adapter; TYPE_3__ uc_swdec_pending_queue; TYPE_3__ recv_pending_queue; int /*<<< orphan*/  lock; } ;
struct adapter {int dummy; } ;
typedef  int sint ;
typedef  int /*<<< orphan*/  SIZE_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NR_RECVFRAME ; 
 scalar_t__ N_BYTE_ALIGMENT (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RXFRAME_ALIGN_SZ ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _rtw_init_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rtw_hal_init_recv_priv (struct adapter*) ; 
 int /*<<< orphan*/  rtw_os_recv_resource_alloc (struct adapter*,union recv_frame*) ; 
 int /*<<< orphan*/  rtw_set_signal_stat_timer (struct recv_priv*) ; 
 int /*<<< orphan*/  rtw_signal_stat_timer_hdl ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vzalloc (scalar_t__) ; 

sint _rtw_init_recv_priv(struct recv_priv *precvpriv, struct adapter *padapter)
{
	sint i;
	union recv_frame *precvframe;
	sint	res = _SUCCESS;

	spin_lock_init(&precvpriv->lock);

	_rtw_init_queue(&precvpriv->free_recv_queue);
	_rtw_init_queue(&precvpriv->recv_pending_queue);
	_rtw_init_queue(&precvpriv->uc_swdec_pending_queue);

	precvpriv->adapter = padapter;

	precvpriv->free_recvframe_cnt = NR_RECVFRAME;

	precvpriv->pallocated_frame_buf = vzalloc(NR_RECVFRAME * sizeof(union recv_frame) + RXFRAME_ALIGN_SZ);

	if (!precvpriv->pallocated_frame_buf) {
		res = _FAIL;
		goto exit;
	}

	precvpriv->precv_frame_buf = (u8 *)N_BYTE_ALIGMENT((SIZE_PTR)(precvpriv->pallocated_frame_buf), RXFRAME_ALIGN_SZ);
	/* precvpriv->precv_frame_buf = precvpriv->pallocated_frame_buf + RXFRAME_ALIGN_SZ - */
	/* 						((SIZE_PTR) (precvpriv->pallocated_frame_buf) &(RXFRAME_ALIGN_SZ-1)); */

	precvframe = (union recv_frame *) precvpriv->precv_frame_buf;


	for (i = 0; i < NR_RECVFRAME; i++) {
		INIT_LIST_HEAD(&(precvframe->u.list));

		list_add_tail(&(precvframe->u.list), &(precvpriv->free_recv_queue.queue));

		rtw_os_recv_resource_alloc(padapter, precvframe);

		precvframe->u.hdr.len = 0;

		precvframe->u.hdr.adapter = padapter;
		precvframe++;

	}

	res = rtw_hal_init_recv_priv(padapter);

	timer_setup(&precvpriv->signal_stat_timer, rtw_signal_stat_timer_hdl,
		    0);

	precvpriv->signal_stat_sampling_interval = 2000; /* ms */

	rtw_set_signal_stat_timer(precvpriv);

exit:
	return res;
}