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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 unsigned long MPX_BD_ENTRY_VALID_FLAG ; 
 scalar_t__ is_64bit_mm (struct mm_struct*) ; 

__attribute__((used)) static unsigned long mpx_bd_entry_to_bt_addr(struct mm_struct *mm,
					     unsigned long bd_entry)
{
	unsigned long bt_addr = bd_entry;
	int align_to_bytes;
	/*
	 * Bit 0 in a bt_entry is always the valid bit.
	 */
	bt_addr &= ~MPX_BD_ENTRY_VALID_FLAG;
	/*
	 * Tables are naturally aligned at 8-byte boundaries
	 * on 64-bit and 4-byte boundaries on 32-bit.  The
	 * documentation makes it appear that the low bits
	 * are ignored by the hardware, so we do the same.
	 */
	if (is_64bit_mm(mm))
		align_to_bytes = 8;
	else
		align_to_bytes = 4;
	bt_addr &= ~(align_to_bytes-1);
	return bt_addr;
}