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
typedef  int /*<<< orphan*/  u32 ;
struct nfp6000_pcie {int /*<<< orphan*/  bar_lock; int /*<<< orphan*/ * bar; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __acquire (int /*<<< orphan*/ *) ; 
 int find_matching_bar (struct nfp6000_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int) ; 
 int find_unused_bar_noblock (struct nfp6000_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  nfp_bar_get (struct nfp6000_pcie*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_bar_put (struct nfp6000_pcie*,int /*<<< orphan*/ *) ; 
 int nfp_wait_for_bar (struct nfp6000_pcie*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int) ; 
 int reconfigure_bar (struct nfp6000_pcie*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
nfp_alloc_bar(struct nfp6000_pcie *nfp,
	      u32 tgt, u32 act, u32 tok,
	      u64 offset, size_t size, int width, int nonblocking)
{
	unsigned long irqflags;
	int barnum, retval;

	if (size > (1 << 24))
		return -EINVAL;

	spin_lock_irqsave(&nfp->bar_lock, irqflags);
	barnum = find_matching_bar(nfp, tgt, act, tok, offset, size, width);
	if (barnum >= 0) {
		/* Found a perfect match. */
		nfp_bar_get(nfp, &nfp->bar[barnum]);
		spin_unlock_irqrestore(&nfp->bar_lock, irqflags);
		return barnum;
	}

	barnum = find_unused_bar_noblock(nfp, tgt, act, tok,
					 offset, size, width);
	if (barnum < 0) {
		if (nonblocking)
			goto err_nobar;

		/* Wait until a BAR becomes available.  The
		 * find_unused_bar function will reclaim the bar_lock
		 * if a free BAR is found.
		 */
		spin_unlock_irqrestore(&nfp->bar_lock, irqflags);
		retval = nfp_wait_for_bar(nfp, &barnum, tgt, act, tok,
					  offset, size, width);
		if (retval)
			return retval;
		__acquire(&nfp->bar_lock);
	}

	nfp_bar_get(nfp, &nfp->bar[barnum]);
	retval = reconfigure_bar(nfp, &nfp->bar[barnum],
				 tgt, act, tok, offset, size, width);
	if (retval < 0) {
		nfp_bar_put(nfp, &nfp->bar[barnum]);
		barnum = retval;
	}

err_nobar:
	spin_unlock_irqrestore(&nfp->bar_lock, irqflags);
	return barnum;
}