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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;
struct xmit_priv {int free_xmitframe_cnt; int free_xmitbuf_cnt; int free_xmit_extbuf_cnt; int* wmm_para_seq; int txirp_cnt; int ack_tx; int /*<<< orphan*/  ack_tx_ops; int /*<<< orphan*/  ack_tx_mutex; scalar_t__ voq_cnt; scalar_t__ viq_cnt; scalar_t__ bkq_cnt; scalar_t__ beq_cnt; int /*<<< orphan*/  hwxmit_entry; int /*<<< orphan*/  hwxmits; TYPE_1__ free_xmit_extbuf_queue; void* pxmit_extbuf; void* pallocated_xmit_extbuf; TYPE_1__ free_xmitbuf_queue; void* pxmitbuf; void* pallocated_xmitbuf; TYPE_1__ pending_xmitbuf_queue; int /*<<< orphan*/  frag_len; TYPE_1__ free_xmit_queue; int /*<<< orphan*/ * pxmit_frame_buf; void* pallocated_frame_buf; TYPE_1__ bm_pending; TYPE_1__ vo_pending; TYPE_1__ vi_pending; TYPE_1__ bk_pending; TYPE_1__ be_pending; struct adapter* adapter; int /*<<< orphan*/  lock; } ;
struct xmit_frame {int /*<<< orphan*/  list; int /*<<< orphan*/ * pxmitbuf; int /*<<< orphan*/ * buf_addr; int /*<<< orphan*/ * pkt; int /*<<< orphan*/  frame_tag; struct adapter* padapter; } ;
struct xmit_buf {int ext_tag; int /*<<< orphan*/  list; struct adapter* padapter; int /*<<< orphan*/ * priv_data; int /*<<< orphan*/  flags; } ;
struct adapter {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_FRAG_THRESHOLD ; 
 int MAX_XMITBUF_SZ ; 
 int MAX_XMIT_EXTBUF_SZ ; 
 int NR_XMITBUFF ; 
 int NR_XMITFRAME ; 
 int NR_XMIT_EXTBUFF ; 
 int /*<<< orphan*/  NULL_FRAMETAG ; 
 void* PTR_ALIGN (void*,int) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int XMITBUF_ALIGN_SZ ; 
 int /*<<< orphan*/  XMIT_VO_QUEUE ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_xmit_c_ ; 
 int /*<<< orphan*/  _rtw_init_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int rtw_alloc_hwxmits (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_init_xmit_priv (struct adapter*) ; 
 int /*<<< orphan*/  rtw_init_hwxmits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtw_os_xmit_resource_alloc (struct adapter*,struct xmit_buf*,int) ; 
 int /*<<< orphan*/  rtw_sctx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 void* vzalloc (int) ; 

s32 _rtw_init_xmit_priv(struct xmit_priv *pxmitpriv, struct adapter *padapter)
{
	int i;
	struct xmit_buf *pxmitbuf;
	struct xmit_frame *pxframe;
	int res = _SUCCESS;
	u32 max_xmit_extbuf_size = MAX_XMIT_EXTBUF_SZ;
	u32 num_xmit_extbuf = NR_XMIT_EXTBUFF;

	/*  We don't need to memset padapter->XXX to zero, because adapter is allocated by vzalloc(). */

	spin_lock_init(&pxmitpriv->lock);

	/*
	Please insert all the queue initializaiton using _rtw_init_queue below
	*/

	pxmitpriv->adapter = padapter;

	_rtw_init_queue(&pxmitpriv->be_pending);
	_rtw_init_queue(&pxmitpriv->bk_pending);
	_rtw_init_queue(&pxmitpriv->vi_pending);
	_rtw_init_queue(&pxmitpriv->vo_pending);
	_rtw_init_queue(&pxmitpriv->bm_pending);

	_rtw_init_queue(&pxmitpriv->free_xmit_queue);

	/*
	Please allocate memory with the sz = (struct xmit_frame) * NR_XMITFRAME,
	and initialize free_xmit_frame below.
	Please also apply  free_txobj to link_up all the xmit_frames...
	*/

	pxmitpriv->pallocated_frame_buf = vzalloc(NR_XMITFRAME * sizeof(struct xmit_frame) + 4);

	if (!pxmitpriv->pallocated_frame_buf) {
		pxmitpriv->pxmit_frame_buf = NULL;
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("alloc xmit_frame fail!\n"));
		res = _FAIL;
		goto exit;
	}
	pxmitpriv->pxmit_frame_buf = PTR_ALIGN(pxmitpriv->pallocated_frame_buf, 4);

	pxframe = (struct xmit_frame *)pxmitpriv->pxmit_frame_buf;

	for (i = 0; i < NR_XMITFRAME; i++) {
		INIT_LIST_HEAD(&pxframe->list);

		pxframe->padapter = padapter;
		pxframe->frame_tag = NULL_FRAMETAG;

		pxframe->pkt = NULL;

		pxframe->buf_addr = NULL;
		pxframe->pxmitbuf = NULL;

		list_add_tail(&pxframe->list, &pxmitpriv->free_xmit_queue.queue);

		pxframe++;
	}

	pxmitpriv->free_xmitframe_cnt = NR_XMITFRAME;

	pxmitpriv->frag_len = MAX_FRAG_THRESHOLD;

	/* init xmit_buf */
	_rtw_init_queue(&pxmitpriv->free_xmitbuf_queue);
	_rtw_init_queue(&pxmitpriv->pending_xmitbuf_queue);

	pxmitpriv->pallocated_xmitbuf = vzalloc(NR_XMITBUFF * sizeof(struct xmit_buf) + 4);

	if (!pxmitpriv->pallocated_xmitbuf) {
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("alloc xmit_buf fail!\n"));
		res = _FAIL;
		goto exit;
	}

	pxmitpriv->pxmitbuf = PTR_ALIGN(pxmitpriv->pallocated_xmitbuf, 4);

	pxmitbuf = (struct xmit_buf *)pxmitpriv->pxmitbuf;

	for (i = 0; i < NR_XMITBUFF; i++) {
		INIT_LIST_HEAD(&pxmitbuf->list);

		pxmitbuf->priv_data = NULL;
		pxmitbuf->padapter = padapter;
		pxmitbuf->ext_tag = false;

		/* Tx buf allocation may fail sometimes, so sleep and retry. */
		res = rtw_os_xmit_resource_alloc(padapter, pxmitbuf, (MAX_XMITBUF_SZ + XMITBUF_ALIGN_SZ));
		if (res == _FAIL) {
			msleep(10);
			res = rtw_os_xmit_resource_alloc(padapter, pxmitbuf, (MAX_XMITBUF_SZ + XMITBUF_ALIGN_SZ));
			if (res == _FAIL)
				goto exit;
		}

		pxmitbuf->flags = XMIT_VO_QUEUE;

		list_add_tail(&pxmitbuf->list, &pxmitpriv->free_xmitbuf_queue.queue);
		pxmitbuf++;
	}

	pxmitpriv->free_xmitbuf_cnt = NR_XMITBUFF;

	/*  Init xmit extension buff */
	_rtw_init_queue(&pxmitpriv->free_xmit_extbuf_queue);

	pxmitpriv->pallocated_xmit_extbuf = vzalloc(num_xmit_extbuf * sizeof(struct xmit_buf) + 4);

	if (!pxmitpriv->pallocated_xmit_extbuf) {
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_, ("alloc xmit_extbuf fail!\n"));
		res = _FAIL;
		goto exit;
	}

	pxmitpriv->pxmit_extbuf = PTR_ALIGN(pxmitpriv->pallocated_xmit_extbuf, 4);

	pxmitbuf = (struct xmit_buf *)pxmitpriv->pxmit_extbuf;

	for (i = 0; i < num_xmit_extbuf; i++) {
		INIT_LIST_HEAD(&pxmitbuf->list);

		pxmitbuf->priv_data = NULL;
		pxmitbuf->padapter = padapter;
		pxmitbuf->ext_tag = true;

		res = rtw_os_xmit_resource_alloc(padapter, pxmitbuf, max_xmit_extbuf_size + XMITBUF_ALIGN_SZ);
		if (res == _FAIL) {
			res = _FAIL;
			goto exit;
		}

		list_add_tail(&pxmitbuf->list, &pxmitpriv->free_xmit_extbuf_queue.queue);
		pxmitbuf++;
	}

	pxmitpriv->free_xmit_extbuf_cnt = num_xmit_extbuf;

	res = rtw_alloc_hwxmits(padapter);
	if (res == _FAIL)
		goto exit;
	rtw_init_hwxmits(pxmitpriv->hwxmits, pxmitpriv->hwxmit_entry);

	for (i = 0; i < 4; i++)
		pxmitpriv->wmm_para_seq[i] = i;

	pxmitpriv->txirp_cnt = 1;

	/* per AC pending irp */
	pxmitpriv->beq_cnt = 0;
	pxmitpriv->bkq_cnt = 0;
	pxmitpriv->viq_cnt = 0;
	pxmitpriv->voq_cnt = 0;

	pxmitpriv->ack_tx = false;
	mutex_init(&pxmitpriv->ack_tx_mutex);
	rtw_sctx_init(&pxmitpriv->ack_tx_ops, 0);

	rtw_hal_init_xmit_priv(padapter);

exit:
	return res;
}