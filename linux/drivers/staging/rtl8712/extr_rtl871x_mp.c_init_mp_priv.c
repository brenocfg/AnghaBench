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
struct mp_xmit_frame {int /*<<< orphan*/  padapter; int /*<<< orphan*/  frame_tag; int /*<<< orphan*/ * pkt; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;
struct mp_priv {int free_mp_xmitframe_cnt; int /*<<< orphan*/  papdater; TYPE_1__ free_mp_xmitqueue; int /*<<< orphan*/ * pmp_xmtframe_buf; int /*<<< orphan*/ * pallocated_mp_xmitframe_buf; } ;
typedef  int addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP_FRAMETAG ; 
 int NR_MP_XMITFRAME ; 
 int /*<<< orphan*/  _init_mp_priv_ (struct mp_priv*) ; 
 int /*<<< orphan*/  _init_queue (TYPE_1__*) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_mp_priv(struct mp_priv *pmp_priv)
{
	int i;
	struct mp_xmit_frame *pmp_xmitframe;

	_init_mp_priv_(pmp_priv);
	_init_queue(&pmp_priv->free_mp_xmitqueue);
	pmp_priv->pallocated_mp_xmitframe_buf = NULL;
	pmp_priv->pallocated_mp_xmitframe_buf = kmalloc(NR_MP_XMITFRAME *
				sizeof(struct mp_xmit_frame) + 4,
				GFP_ATOMIC);
	if (!pmp_priv->pallocated_mp_xmitframe_buf) {
		return -ENOMEM;
	}
	pmp_priv->pmp_xmtframe_buf = pmp_priv->pallocated_mp_xmitframe_buf +
			 4 -
			 ((addr_t)(pmp_priv->pallocated_mp_xmitframe_buf) & 3);
	pmp_xmitframe = (struct mp_xmit_frame *)pmp_priv->pmp_xmtframe_buf;
	for (i = 0; i < NR_MP_XMITFRAME; i++) {
		INIT_LIST_HEAD(&(pmp_xmitframe->list));
		list_add_tail(&(pmp_xmitframe->list),
				 &(pmp_priv->free_mp_xmitqueue.queue));
		pmp_xmitframe->pkt = NULL;
		pmp_xmitframe->frame_tag = MP_FRAMETAG;
		pmp_xmitframe->padapter = pmp_priv->papdater;
		pmp_xmitframe++;
	}
	pmp_priv->free_mp_xmitframe_cnt = NR_MP_XMITFRAME;
	return 0;
}