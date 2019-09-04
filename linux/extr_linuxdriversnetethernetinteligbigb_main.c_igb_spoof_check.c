#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct igb_adapter {int wvbr; int vfs_allocated_count; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int IGB_STAGGERED_QUEUE_OFFSET ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void igb_spoof_check(struct igb_adapter *adapter)
{
	int j;

	if (!adapter->wvbr)
		return;

	for (j = 0; j < adapter->vfs_allocated_count; j++) {
		if (adapter->wvbr & BIT(j) ||
		    adapter->wvbr & BIT(j + IGB_STAGGERED_QUEUE_OFFSET)) {
			dev_warn(&adapter->pdev->dev,
				"Spoof event(s) detected on VF %d\n", j);
			adapter->wvbr &=
				~(BIT(j) |
				  BIT(j + IGB_STAGGERED_QUEUE_OFFSET));
		}
	}
}