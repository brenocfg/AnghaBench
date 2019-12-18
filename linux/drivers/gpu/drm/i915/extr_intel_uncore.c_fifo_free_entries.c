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
typedef  int u32 ;
struct intel_uncore {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GTFIFOCTL ; 
 int GT_FIFO_FREE_ENTRIES_MASK ; 
 int __raw_uncore_read32 (struct intel_uncore*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 fifo_free_entries(struct intel_uncore *uncore)
{
	u32 count = __raw_uncore_read32(uncore, GTFIFOCTL);

	return count & GT_FIFO_FREE_ENTRIES_MASK;
}