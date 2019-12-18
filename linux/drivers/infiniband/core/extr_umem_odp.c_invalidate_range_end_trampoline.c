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
struct ib_umem_odp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_umem_notifier_end_account (struct ib_umem_odp*) ; 

__attribute__((used)) static int invalidate_range_end_trampoline(struct ib_umem_odp *item, u64 start,
					   u64 end, void *cookie)
{
	ib_umem_notifier_end_account(item);
	return 0;
}