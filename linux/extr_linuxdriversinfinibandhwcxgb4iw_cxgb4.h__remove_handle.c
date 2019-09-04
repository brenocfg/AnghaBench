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
typedef  int /*<<< orphan*/  u32 ;
struct idr {int dummy; } ;
struct c4iw_dev {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (struct idr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void _remove_handle(struct c4iw_dev *rhp, struct idr *idr,
				   u32 id, int lock)
{
	if (lock)
		spin_lock_irq(&rhp->lock);
	idr_remove(idr, id);
	if (lock)
		spin_unlock_irq(&rhp->lock);
}