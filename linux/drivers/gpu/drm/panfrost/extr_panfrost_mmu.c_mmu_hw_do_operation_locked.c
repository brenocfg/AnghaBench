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
typedef  scalar_t__ u32 ;
struct panfrost_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ AS_COMMAND_UNLOCK ; 
 int /*<<< orphan*/  lock_region (struct panfrost_device*,int,int /*<<< orphan*/ ,size_t) ; 
 int wait_ready (struct panfrost_device*,int) ; 
 int /*<<< orphan*/  write_cmd (struct panfrost_device*,int,scalar_t__) ; 

__attribute__((used)) static int mmu_hw_do_operation_locked(struct panfrost_device *pfdev, int as_nr,
				      u64 iova, size_t size, u32 op)
{
	if (as_nr < 0)
		return 0;

	if (op != AS_COMMAND_UNLOCK)
		lock_region(pfdev, as_nr, iova, size);

	/* Run the MMU operation */
	write_cmd(pfdev, as_nr, op);

	/* Wait for the flush to complete */
	return wait_ready(pfdev, as_nr);
}