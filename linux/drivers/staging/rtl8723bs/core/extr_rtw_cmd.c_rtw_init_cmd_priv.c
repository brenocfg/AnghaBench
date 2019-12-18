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
struct cmd_priv {int cmd_seq; int /*<<< orphan*/  sctx_mutex; scalar_t__ rsp_cnt; scalar_t__ cmd_done_cnt; scalar_t__ cmd_issued_cnt; void* rsp_allocated_buf; void* rsp_buf; void* cmd_allocated_buf; void* cmd_buf; int /*<<< orphan*/  cmd_queue; int /*<<< orphan*/  terminate_cmdthread_comp; int /*<<< orphan*/  cmd_queue_comp; } ;
typedef  int SIZE_PTR ;

/* Variables and functions */
 int CMDBUFF_ALIGN_SZ ; 
 int ENOMEM ; 
 scalar_t__ MAX_CMDSZ ; 
 scalar_t__ MAX_RSPSZ ; 
 int /*<<< orphan*/  _rtw_init_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 void* rtw_zmalloc (scalar_t__) ; 

int rtw_init_cmd_priv(struct	cmd_priv *pcmdpriv)
{
	int res = 0;

	init_completion(&pcmdpriv->cmd_queue_comp);
	init_completion(&pcmdpriv->terminate_cmdthread_comp);

	_rtw_init_queue(&(pcmdpriv->cmd_queue));

	/* allocate DMA-able/Non-Page memory for cmd_buf and rsp_buf */

	pcmdpriv->cmd_seq = 1;

	pcmdpriv->cmd_allocated_buf = rtw_zmalloc(MAX_CMDSZ + CMDBUFF_ALIGN_SZ);

	if (!pcmdpriv->cmd_allocated_buf) {
		res = -ENOMEM;
		goto exit;
	}

	pcmdpriv->cmd_buf = pcmdpriv->cmd_allocated_buf  +  CMDBUFF_ALIGN_SZ - ((SIZE_PTR)(pcmdpriv->cmd_allocated_buf) & (CMDBUFF_ALIGN_SZ-1));

	pcmdpriv->rsp_allocated_buf = rtw_zmalloc(MAX_RSPSZ + 4);

	if (!pcmdpriv->rsp_allocated_buf) {
		res = -ENOMEM;
		goto exit;
	}

	pcmdpriv->rsp_buf = pcmdpriv->rsp_allocated_buf  +  4 - ((SIZE_PTR)(pcmdpriv->rsp_allocated_buf) & 3);

	pcmdpriv->cmd_issued_cnt = pcmdpriv->cmd_done_cnt = pcmdpriv->rsp_cnt = 0;

	mutex_init(&pcmdpriv->sctx_mutex);
exit:
	return res;
}