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
struct xmit_priv {int free_xmitframe_cnt; int txirp_cnt; int free_xmitbuf_cnt; int /*<<< orphan*/  xmit_tasklet; int /*<<< orphan*/  hwxmit_entry; int /*<<< orphan*/  hwxmits; TYPE_1__ free_xmitbuf_queue; void* pxmitbuf; void* pallocated_xmitbuf; int /*<<< orphan*/ * pallocated_frame_buf; TYPE_1__ pending_xmitbuf_queue; scalar_t__ voq_cnt; scalar_t__ viq_cnt; scalar_t__ bkq_cnt; scalar_t__ beq_cnt; int /*<<< orphan*/  frag_len; int /*<<< orphan*/  bmc_txqueue; int /*<<< orphan*/  vo_txqueue; int /*<<< orphan*/  vi_txqueue; int /*<<< orphan*/  bk_txqueue; int /*<<< orphan*/  be_txqueue; TYPE_1__ free_xmit_queue; int /*<<< orphan*/ * pxmit_frame_buf; TYPE_1__ apsd_queue; TYPE_1__ legacy_dz_queue; TYPE_1__ bm_pending; TYPE_1__ vo_pending; TYPE_1__ vi_pending; TYPE_1__ bk_pending; TYPE_1__ be_pending; struct _adapter* adapter; int /*<<< orphan*/  lock; } ;
struct xmit_frame {int /*<<< orphan*/  list; int /*<<< orphan*/ * pxmitbuf; int /*<<< orphan*/ * buf_addr; int /*<<< orphan*/ * pkt; int /*<<< orphan*/  frame_tag; struct _adapter* padapter; } ;
struct xmit_buf {int /*<<< orphan*/  list; void* pallocated_buf; void* pbuf; } ;
struct _adapter {int /*<<< orphan*/  wk_filter_rx_ff0; } ;
typedef  int sint ;
typedef  int addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BE_QUEUE_INX ; 
 int /*<<< orphan*/  BK_QUEUE_INX ; 
 int /*<<< orphan*/  BMC_QUEUE_INX ; 
 int /*<<< orphan*/  DATA_FRAMETAG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_FRAG_THRESHOLD ; 
 int MAX_XMITBUF_SZ ; 
 int NR_XMITBUFF ; 
 int NR_XMITFRAME ; 
 int /*<<< orphan*/  VI_QUEUE_INX ; 
 int /*<<< orphan*/  VO_QUEUE_INX ; 
 int XMITBUF_ALIGN_SZ ; 
 int /*<<< orphan*/  _init_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  _r8712_init_hw_txqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_hwxmits (struct _adapter*) ; 
 int /*<<< orphan*/  init_hwxmits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r8712_SetFilter ; 
 scalar_t__ r8712_xmit_bh ; 
 scalar_t__ r8712_xmit_resource_alloc (struct _adapter*,struct xmit_buf*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,void (*) (unsigned long),unsigned long) ; 

int _r8712_init_xmit_priv(struct xmit_priv *pxmitpriv,
			  struct _adapter *padapter)
{
	sint i;
	struct xmit_buf *pxmitbuf;
	struct xmit_frame *pxframe;

	memset((unsigned char *)pxmitpriv, 0, sizeof(struct xmit_priv));
	spin_lock_init(&pxmitpriv->lock);
	/*
	 *Please insert all the queue initialization using _init_queue below
	 */
	pxmitpriv->adapter = padapter;
	_init_queue(&pxmitpriv->be_pending);
	_init_queue(&pxmitpriv->bk_pending);
	_init_queue(&pxmitpriv->vi_pending);
	_init_queue(&pxmitpriv->vo_pending);
	_init_queue(&pxmitpriv->bm_pending);
	_init_queue(&pxmitpriv->legacy_dz_queue);
	_init_queue(&pxmitpriv->apsd_queue);
	_init_queue(&pxmitpriv->free_xmit_queue);
	/*
	 * Please allocate memory with the sz = (struct xmit_frame) * NR_XMITFRAME,
	 * and initialize free_xmit_frame below.
	 * Please also apply  free_txobj to link_up all the xmit_frames...
	 */
	pxmitpriv->pallocated_frame_buf =
		kmalloc(NR_XMITFRAME * sizeof(struct xmit_frame) + 4, GFP_ATOMIC);
	if (!pxmitpriv->pallocated_frame_buf) {
		pxmitpriv->pxmit_frame_buf = NULL;
		return -ENOMEM;
	}
	pxmitpriv->pxmit_frame_buf = pxmitpriv->pallocated_frame_buf + 4 -
			((addr_t) (pxmitpriv->pallocated_frame_buf) & 3);
	pxframe = (struct xmit_frame *) pxmitpriv->pxmit_frame_buf;
	for (i = 0; i < NR_XMITFRAME; i++) {
		INIT_LIST_HEAD(&(pxframe->list));
		pxframe->padapter = padapter;
		pxframe->frame_tag = DATA_FRAMETAG;
		pxframe->pkt = NULL;
		pxframe->buf_addr = NULL;
		pxframe->pxmitbuf = NULL;
		list_add_tail(&(pxframe->list),
				 &(pxmitpriv->free_xmit_queue.queue));
		pxframe++;
	}
	pxmitpriv->free_xmitframe_cnt = NR_XMITFRAME;
	/*
	 * init xmit hw_txqueue
	 */
	_r8712_init_hw_txqueue(&pxmitpriv->be_txqueue, BE_QUEUE_INX);
	_r8712_init_hw_txqueue(&pxmitpriv->bk_txqueue, BK_QUEUE_INX);
	_r8712_init_hw_txqueue(&pxmitpriv->vi_txqueue, VI_QUEUE_INX);
	_r8712_init_hw_txqueue(&pxmitpriv->vo_txqueue, VO_QUEUE_INX);
	_r8712_init_hw_txqueue(&pxmitpriv->bmc_txqueue, BMC_QUEUE_INX);
	pxmitpriv->frag_len = MAX_FRAG_THRESHOLD;
	pxmitpriv->txirp_cnt = 1;
	/*per AC pending irp*/
	pxmitpriv->beq_cnt = 0;
	pxmitpriv->bkq_cnt = 0;
	pxmitpriv->viq_cnt = 0;
	pxmitpriv->voq_cnt = 0;
	/*init xmit_buf*/
	_init_queue(&pxmitpriv->free_xmitbuf_queue);
	_init_queue(&pxmitpriv->pending_xmitbuf_queue);
	pxmitpriv->pallocated_xmitbuf =
		kmalloc(NR_XMITBUFF * sizeof(struct xmit_buf) + 4, GFP_ATOMIC);
	if (!pxmitpriv->pallocated_xmitbuf) {
		kfree(pxmitpriv->pallocated_frame_buf);
		pxmitpriv->pallocated_frame_buf = NULL;
		return -ENOMEM;
	}
	pxmitpriv->pxmitbuf = pxmitpriv->pallocated_xmitbuf + 4 -
			      ((addr_t)(pxmitpriv->pallocated_xmitbuf) & 3);
	pxmitbuf = (struct xmit_buf *)pxmitpriv->pxmitbuf;
	for (i = 0; i < NR_XMITBUFF; i++) {
		INIT_LIST_HEAD(&pxmitbuf->list);
		pxmitbuf->pallocated_buf = kmalloc(MAX_XMITBUF_SZ + XMITBUF_ALIGN_SZ,
						   GFP_ATOMIC);
		if (!pxmitbuf->pallocated_buf)
			return -ENOMEM;
		pxmitbuf->pbuf = pxmitbuf->pallocated_buf + XMITBUF_ALIGN_SZ -
				 ((addr_t) (pxmitbuf->pallocated_buf) &
				 (XMITBUF_ALIGN_SZ - 1));
		if (r8712_xmit_resource_alloc(padapter, pxmitbuf))
			return -ENOMEM;
		list_add_tail(&pxmitbuf->list,
				 &(pxmitpriv->free_xmitbuf_queue.queue));
		pxmitbuf++;
	}
	pxmitpriv->free_xmitbuf_cnt = NR_XMITBUFF;
	INIT_WORK(&padapter->wk_filter_rx_ff0, r8712_SetFilter);
	alloc_hwxmits(padapter);
	init_hwxmits(pxmitpriv->hwxmits, pxmitpriv->hwxmit_entry);
	tasklet_init(&pxmitpriv->xmit_tasklet,
		(void(*)(unsigned long))r8712_xmit_bh,
		(unsigned long)padapter);
	return 0;
}