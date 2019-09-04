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
typedef  scalar_t__ u32 ;
struct idr {int dummy; } ;
struct c4iw_dev {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int idr_alloc (struct idr*,void*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int _insert_handle(struct c4iw_dev *rhp, struct idr *idr,
				 void *handle, u32 id, int lock)
{
	int ret;

	if (lock) {
		idr_preload(GFP_KERNEL);
		spin_lock_irq(&rhp->lock);
	}

	ret = idr_alloc(idr, handle, id, id + 1, GFP_ATOMIC);

	if (lock) {
		spin_unlock_irq(&rhp->lock);
		idr_preload_end();
	}

	return ret < 0 ? ret : 0;
}