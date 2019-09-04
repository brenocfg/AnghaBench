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
struct uld_msix_bmap {unsigned int mapsize; int /*<<< orphan*/  lock; int /*<<< orphan*/  msix_bmap; } ;
struct adapter {struct uld_msix_bmap msix_bmap_ulds; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  __set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int find_first_zero_bit (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int get_msix_idx_from_bmap(struct adapter *adap)
{
	struct uld_msix_bmap *bmap = &adap->msix_bmap_ulds;
	unsigned long flags;
	unsigned int msix_idx;

	spin_lock_irqsave(&bmap->lock, flags);
	msix_idx = find_first_zero_bit(bmap->msix_bmap, bmap->mapsize);
	if (msix_idx < bmap->mapsize) {
		__set_bit(msix_idx, bmap->msix_bmap);
	} else {
		spin_unlock_irqrestore(&bmap->lock, flags);
		return -ENOSPC;
	}

	spin_unlock_irqrestore(&bmap->lock, flags);
	return msix_idx;
}