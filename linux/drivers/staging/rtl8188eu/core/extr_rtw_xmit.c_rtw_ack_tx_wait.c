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
typedef  int /*<<< orphan*/  u32 ;
struct submit_ctx {int /*<<< orphan*/  status; int /*<<< orphan*/  timeout_ms; int /*<<< orphan*/  submit_time; } ;
struct xmit_priv {struct submit_ctx ack_tx_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTW_SCTX_SUBMITTED ; 
 int /*<<< orphan*/  jiffies ; 
 int rtw_sctx_wait (struct submit_ctx*) ; 

int rtw_ack_tx_wait(struct xmit_priv *pxmitpriv, u32 timeout_ms)
{
	struct submit_ctx *pack_tx_ops = &pxmitpriv->ack_tx_ops;

	pack_tx_ops->submit_time = jiffies;
	pack_tx_ops->timeout_ms = timeout_ms;
	pack_tx_ops->status = RTW_SCTX_SUBMITTED;

	return rtw_sctx_wait(pack_tx_ops);
}