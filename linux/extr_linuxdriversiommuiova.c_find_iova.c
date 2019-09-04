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
struct iova_domain {int /*<<< orphan*/  iova_rbtree_lock; } ;
struct iova {int dummy; } ;

/* Variables and functions */
 struct iova* private_find_iova (struct iova_domain*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct iova *find_iova(struct iova_domain *iovad, unsigned long pfn)
{
	unsigned long flags;
	struct iova *iova;

	/* Take the lock so that no other thread is manipulating the rbtree */
	spin_lock_irqsave(&iovad->iova_rbtree_lock, flags);
	iova = private_find_iova(iovad, pfn);
	spin_unlock_irqrestore(&iovad->iova_rbtree_lock, flags);
	return iova;
}