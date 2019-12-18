#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct __queue {int dummy; } ;
struct recv_priv {int /*<<< orphan*/  rx_drop; struct __queue free_recv_queue; } ;
struct recv_frame {int dummy; } ;
struct adapter {struct recv_priv recvpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_CTL_RX ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 int /*<<< orphan*/  count_rx_stats (struct adapter*,struct recv_frame*,int /*<<< orphan*/ *) ; 
 struct recv_frame* decryptor (struct adapter*,struct recv_frame*) ; 
 int /*<<< orphan*/  led_control_8188eu (struct adapter*,int /*<<< orphan*/ ) ; 
 struct recv_frame* portctrl (struct adapter*,struct recv_frame*) ; 
 int process_recv_indicatepkts (struct adapter*,struct recv_frame*) ; 
 struct recv_frame* recvframe_chk_defrag (struct adapter*,struct recv_frame*) ; 
 int /*<<< orphan*/  rtw_free_recvframe (struct recv_frame*,struct __queue*) ; 

__attribute__((used)) static int recv_func_posthandle(struct adapter *padapter,
				struct recv_frame *prframe)
{
	int ret = _SUCCESS;
	struct recv_frame *orig_prframe = prframe;
	struct recv_priv *precvpriv = &padapter->recvpriv;
	struct __queue *pfree_recv_queue = &padapter->recvpriv.free_recv_queue;

	/*  DATA FRAME */
	led_control_8188eu(padapter, LED_CTL_RX);

	prframe = decryptor(padapter, prframe);
	if (!prframe) {
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("decryptor: drop pkt\n"));
		ret = _FAIL;
		goto _recv_data_drop;
	}

	prframe = recvframe_chk_defrag(padapter, prframe);
	if (!prframe) {
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("recvframe_chk_defrag: drop pkt\n"));
		goto _recv_data_drop;
	}

	prframe = portctrl(padapter, prframe);
	if (!prframe) {
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("portctrl: drop pkt\n"));
		ret = _FAIL;
		goto _recv_data_drop;
	}

	count_rx_stats(padapter, prframe, NULL);

	ret = process_recv_indicatepkts(padapter, prframe);
	if (ret != _SUCCESS) {
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("recv_func: process_recv_indicatepkts fail!\n"));
		rtw_free_recvframe(orig_prframe, pfree_recv_queue);/* free this recv_frame */
		goto _recv_data_drop;
	}
	return ret;

_recv_data_drop:
	precvpriv->rx_drop++;
	return ret;
}