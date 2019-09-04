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
typedef  int /*<<< orphan*/  u64 ;
struct nfp6000_pcie {int /*<<< orphan*/  bar_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __release (int /*<<< orphan*/ *) ; 
 int find_unused_bar_noblock (struct nfp6000_pcie*,int,int,int,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
find_unused_bar_and_lock(struct nfp6000_pcie *nfp,
			 int tgt, int act, int tok,
			 u64 offset, size_t size, int width)
{
	unsigned long flags;
	int n;

	spin_lock_irqsave(&nfp->bar_lock, flags);

	n = find_unused_bar_noblock(nfp, tgt, act, tok, offset, size, width);
	if (n < 0)
		spin_unlock_irqrestore(&nfp->bar_lock, flags);
	else
		__release(&nfp->bar_lock);

	return n;
}