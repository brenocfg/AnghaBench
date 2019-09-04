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
typedef  unsigned long u16 ;
struct intel_guc {int /*<<< orphan*/  doorbell_bitmap; } ;

/* Variables and functions */
 scalar_t__ GUC_CLIENT_PRIORITY_HIGH ; 
 int GUC_NUM_DOORBELLS ; 
 unsigned long find_next_zero_bit (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

__attribute__((used)) static bool available_dbs(struct intel_guc *guc, u32 priority)
{
	unsigned long offset;
	unsigned long end;
	u16 id;

	/* first half is used for normal priority, second half for high */
	offset = 0;
	end = GUC_NUM_DOORBELLS / 2;
	if (priority <= GUC_CLIENT_PRIORITY_HIGH) {
		offset = end;
		end += offset;
	}

	id = find_next_zero_bit(guc->doorbell_bitmap, end, offset);
	if (id < end)
		return true;

	return false;
}