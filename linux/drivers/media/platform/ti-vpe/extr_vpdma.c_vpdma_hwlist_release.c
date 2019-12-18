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
struct vpdma_data {int* hwlist_used; int /*<<< orphan*/  lock; void* hwlist_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void *vpdma_hwlist_release(struct vpdma_data *vpdma, int list_num)
{
	void *priv;
	unsigned long flags;

	spin_lock_irqsave(&vpdma->lock, flags);
	vpdma->hwlist_used[list_num] = false;
	priv = vpdma->hwlist_priv;
	spin_unlock_irqrestore(&vpdma->lock, flags);

	return priv;
}