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
struct evt_priv {int c2h_wk_alive; int /*<<< orphan*/  c2h_queue; int /*<<< orphan*/  c2h_wk; scalar_t__ evt_done_cnt; int /*<<< orphan*/  event_seq; } ;

/* Variables and functions */
 scalar_t__ C2H_QUEUE_MAX_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  _init_workitem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c2h_wk_callback ; 
 int /*<<< orphan*/  rtw_cbuf_alloc (scalar_t__) ; 

int rtw_init_evt_priv(struct evt_priv *pevtpriv)
{
	/* allocate DMA-able/Non-Page memory for cmd_buf and rsp_buf */
	atomic_set(&pevtpriv->event_seq, 0);
	pevtpriv->evt_done_cnt = 0;

	_init_workitem(&pevtpriv->c2h_wk, c2h_wk_callback, NULL);
	pevtpriv->c2h_wk_alive = false;
	pevtpriv->c2h_queue = rtw_cbuf_alloc(C2H_QUEUE_MAX_LEN+1);
	if (!pevtpriv->c2h_queue)
		return -ENOMEM;

	return 0;
}