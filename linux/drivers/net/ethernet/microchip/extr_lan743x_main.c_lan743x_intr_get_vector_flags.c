#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* vector_list; } ;
struct lan743x_adapter {TYPE_2__ intr; } ;
struct TYPE_3__ {int int_mask; int flags; } ;

/* Variables and functions */
 int LAN743X_MAX_VECTOR_COUNT ; 

__attribute__((used)) static u32 lan743x_intr_get_vector_flags(struct lan743x_adapter *adapter,
					 u32 int_mask)
{
	int index;

	for (index = 0; index < LAN743X_MAX_VECTOR_COUNT; index++) {
		if (adapter->intr.vector_list[index].int_mask & int_mask)
			return adapter->intr.vector_list[index].flags;
	}
	return 0;
}