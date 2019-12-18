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
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 void* idr_remove (struct idr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void *mlx5_fpga_tls_release_swid(struct idr *idr,
					spinlock_t *idr_spinlock, u32 swid)
{
	unsigned long flags;
	void *ptr;

	spin_lock_irqsave(idr_spinlock, flags);
	ptr = idr_remove(idr, swid);
	spin_unlock_irqrestore(idr_spinlock, flags);
	return ptr;
}