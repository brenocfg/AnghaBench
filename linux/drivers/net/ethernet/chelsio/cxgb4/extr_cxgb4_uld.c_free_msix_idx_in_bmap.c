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
struct uld_msix_bmap {int /*<<< orphan*/  lock; int /*<<< orphan*/  msix_bmap; } ;
struct adapter {struct uld_msix_bmap msix_bmap_ulds; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void free_msix_idx_in_bmap(struct adapter *adap, unsigned int msix_idx)
{
	struct uld_msix_bmap *bmap = &adap->msix_bmap_ulds;
	unsigned long flags;

	spin_lock_irqsave(&bmap->lock, flags);
	__clear_bit(msix_idx, bmap->msix_bmap);
	spin_unlock_irqrestore(&bmap->lock, flags);
}