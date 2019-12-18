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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hfi1_ibdev {TYPE_1__* fault; } ;
struct TYPE_2__ {int direction; scalar_t__ fault_skip_usec; scalar_t__ skip_usec; scalar_t__ fault_skip; scalar_t__ skip; int /*<<< orphan*/  attr; int /*<<< orphan*/  opcodes; scalar_t__ opcode; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 scalar_t__ bitmap_empty (int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int should_fail (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 
 scalar_t__ usecs_to_jiffies (scalar_t__) ; 

__attribute__((used)) static bool __hfi1_should_fault(struct hfi1_ibdev *ibd, u32 opcode,
				u8 direction)
{
	bool ret = false;

	if (!ibd->fault || !ibd->fault->enable)
		return false;
	if (!(ibd->fault->direction & direction))
		return false;
	if (ibd->fault->opcode) {
		if (bitmap_empty(ibd->fault->opcodes,
				 (sizeof(ibd->fault->opcodes) *
				  BITS_PER_BYTE)))
			return false;
		if (!(test_bit(opcode, ibd->fault->opcodes)))
			return false;
	}
	if (ibd->fault->fault_skip_usec &&
	    time_before(jiffies, ibd->fault->skip_usec))
		return false;
	if (ibd->fault->fault_skip && ibd->fault->skip) {
		ibd->fault->skip--;
		return false;
	}
	ret = should_fail(&ibd->fault->attr, 1);
	if (ret) {
		ibd->fault->skip = ibd->fault->fault_skip;
		ibd->fault->skip_usec = jiffies +
			usecs_to_jiffies(ibd->fault->fault_skip_usec);
	}
	return ret;
}