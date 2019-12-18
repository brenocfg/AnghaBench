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
struct xmit_priv {struct __queue pending_xmitbuf_queue; } ;
typedef  int sint ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

sint check_pending_xmitbuf(
	struct xmit_priv *pxmitpriv)
{
	struct __queue *pqueue;
	sint	ret = false;

	pqueue = &pxmitpriv->pending_xmitbuf_queue;

	spin_lock_bh(&pqueue->lock);

	if (!list_empty(&pqueue->queue))
		ret = true;

	spin_unlock_bh(&pqueue->lock);

	return ret;
}