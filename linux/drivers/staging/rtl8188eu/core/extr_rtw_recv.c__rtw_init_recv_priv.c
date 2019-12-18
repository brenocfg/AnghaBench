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
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;
struct recv_priv {int signal_stat_sampling_interval; int /*<<< orphan*/  signal_stat_timer; TYPE_1__ free_recv_queue; int /*<<< orphan*/  pallocated_frame_buf; struct adapter* adapter; TYPE_1__ uc_swdec_pending_queue; TYPE_1__ recv_pending_queue; } ;
struct recv_frame {struct adapter* adapter; int /*<<< orphan*/ * pkt; int /*<<< orphan*/  list; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NR_RECVFRAME ; 
 struct recv_frame* PTR_ALIGN (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RXFRAME_ALIGN_SZ ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _rtw_init_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rtw_hal_init_recv_priv (struct adapter*) ; 
 int /*<<< orphan*/  rtw_set_signal_stat_timer (struct recv_priv*) ; 
 int /*<<< orphan*/  rtw_signal_stat_timer_hdl ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vzalloc (scalar_t__) ; 

int _rtw_init_recv_priv(struct recv_priv *precvpriv, struct adapter *padapter)
{
	int i;

	struct recv_frame *precvframe;

	int	res = _SUCCESS;

	_rtw_init_queue(&precvpriv->free_recv_queue);
	_rtw_init_queue(&precvpriv->recv_pending_queue);
	_rtw_init_queue(&precvpriv->uc_swdec_pending_queue);

	precvpriv->adapter = padapter;

	precvpriv->pallocated_frame_buf = vzalloc(NR_RECVFRAME * sizeof(struct recv_frame) + RXFRAME_ALIGN_SZ);

	if (!precvpriv->pallocated_frame_buf)
		return _FAIL;

	precvframe = PTR_ALIGN(precvpriv->pallocated_frame_buf, RXFRAME_ALIGN_SZ);

	for (i = 0; i < NR_RECVFRAME; i++) {
		INIT_LIST_HEAD(&precvframe->list);

		list_add_tail(&precvframe->list,
				     &precvpriv->free_recv_queue.queue);

		precvframe->pkt = NULL;

		precvframe->adapter = padapter;
		precvframe++;
	}
	res = rtw_hal_init_recv_priv(padapter);

	timer_setup(&precvpriv->signal_stat_timer, rtw_signal_stat_timer_hdl,
		    0);

	precvpriv->signal_stat_sampling_interval = 1000; /* ms */

	rtw_set_signal_stat_timer(precvpriv);

	return res;
}