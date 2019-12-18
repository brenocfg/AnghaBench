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
struct iova_magazine {int size; int /*<<< orphan*/ * pfns; } ;
struct iova_domain {int /*<<< orphan*/  iova_rbtree_lock; } ;
struct iova {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct iova* private_find_iova (struct iova_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  private_free_iova (struct iova_domain*,struct iova*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
iova_magazine_free_pfns(struct iova_magazine *mag, struct iova_domain *iovad)
{
	unsigned long flags;
	int i;

	if (!mag)
		return;

	spin_lock_irqsave(&iovad->iova_rbtree_lock, flags);

	for (i = 0 ; i < mag->size; ++i) {
		struct iova *iova = private_find_iova(iovad, mag->pfns[i]);

		BUG_ON(!iova);
		private_free_iova(iovad, iova);
	}

	spin_unlock_irqrestore(&iovad->iova_rbtree_lock, flags);

	mag->size = 0;
}