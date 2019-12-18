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
struct __queue {int /*<<< orphan*/  lock; } ;
struct xmit_priv {struct __queue pending_xmitbuf_queue; struct adapter* adapter; } ;
struct xmit_buf {int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  xmit_comp; } ;
struct adapter {TYPE_1__ xmitpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_list_head (struct __queue*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void enqueue_pending_xmitbuf(
	struct xmit_priv *pxmitpriv,
	struct xmit_buf *pxmitbuf)
{
	struct __queue *pqueue;
	struct adapter *pri_adapter = pxmitpriv->adapter;

	pqueue = &pxmitpriv->pending_xmitbuf_queue;

	spin_lock_bh(&pqueue->lock);
	list_del_init(&pxmitbuf->list);
	list_add_tail(&pxmitbuf->list, get_list_head(pqueue));
	spin_unlock_bh(&pqueue->lock);

	complete(&(pri_adapter->xmitpriv.xmit_comp));
}