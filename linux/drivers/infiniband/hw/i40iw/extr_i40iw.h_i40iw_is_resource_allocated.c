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
struct i40iw_device {int /*<<< orphan*/  resource_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static inline bool i40iw_is_resource_allocated(struct i40iw_device *iwdev,
					       unsigned long *resource_array,
					       u32 resource_num)
{
	bool bit_is_set;
	unsigned long flags;

	spin_lock_irqsave(&iwdev->resource_lock, flags);

	bit_is_set = test_bit(resource_num, resource_array);
	spin_unlock_irqrestore(&iwdev->resource_lock, flags);

	return bit_is_set;
}