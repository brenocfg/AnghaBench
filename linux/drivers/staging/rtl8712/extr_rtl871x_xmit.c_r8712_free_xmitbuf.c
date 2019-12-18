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
struct xmit_priv {int /*<<< orphan*/  free_xmitbuf_cnt; struct __queue free_xmitbuf_queue; } ;
struct xmit_buf {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void r8712_free_xmitbuf(struct xmit_priv *pxmitpriv, struct xmit_buf *pxmitbuf)
{
	unsigned long irqL;
	struct  __queue *pfree_xmitbuf_queue = &pxmitpriv->free_xmitbuf_queue;

	if (pxmitbuf == NULL)
		return;
	spin_lock_irqsave(&pfree_xmitbuf_queue->lock, irqL);
	list_del_init(&pxmitbuf->list);
	list_add_tail(&(pxmitbuf->list), &pfree_xmitbuf_queue->queue);
	pxmitpriv->free_xmitbuf_cnt++;
	spin_unlock_irqrestore(&pfree_xmitbuf_queue->lock, irqL);
}