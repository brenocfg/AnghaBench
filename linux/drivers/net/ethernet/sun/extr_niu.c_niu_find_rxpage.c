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
struct rx_ring_info {struct page** rxhash; } ;
struct page {int /*<<< orphan*/  index; int /*<<< orphan*/  mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  PAGE_MASK ; 
 unsigned int niu_hash_rxaddr (struct rx_ring_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct page *niu_find_rxpage(struct rx_ring_info *rp, u64 addr,
				    struct page ***link)
{
	unsigned int h = niu_hash_rxaddr(rp, addr);
	struct page *p, **pp;

	addr &= PAGE_MASK;
	pp = &rp->rxhash[h];
	for (; (p = *pp) != NULL; pp = (struct page **) &p->mapping) {
		if (p->index == addr) {
			*link = pp;
			goto found;
		}
	}
	BUG();

found:
	return p;
}