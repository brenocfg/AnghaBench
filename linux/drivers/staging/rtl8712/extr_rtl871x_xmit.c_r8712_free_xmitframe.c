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
struct __queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct xmit_priv {int /*<<< orphan*/  free_xmitframe_cnt; struct _adapter* adapter; struct __queue free_xmit_queue; } ;
struct xmit_frame {int /*<<< orphan*/  list; int /*<<< orphan*/ * pkt; } ;
struct _adapter {int /*<<< orphan*/  pnetdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void r8712_free_xmitframe(struct xmit_priv *pxmitpriv,
			  struct xmit_frame *pxmitframe)
{
	unsigned long irqL;
	struct  __queue *pfree_xmit_queue = &pxmitpriv->free_xmit_queue;
	struct _adapter *padapter = pxmitpriv->adapter;

	if (pxmitframe == NULL)
		return;
	spin_lock_irqsave(&pfree_xmit_queue->lock, irqL);
	list_del_init(&pxmitframe->list);
	if (pxmitframe->pkt)
		pxmitframe->pkt = NULL;
	list_add_tail(&pxmitframe->list, &pfree_xmit_queue->queue);
	pxmitpriv->free_xmitframe_cnt++;
	spin_unlock_irqrestore(&pfree_xmit_queue->lock, irqL);
	if (netif_queue_stopped(padapter->pnetdev))
		netif_wake_queue(padapter->pnetdev);
}