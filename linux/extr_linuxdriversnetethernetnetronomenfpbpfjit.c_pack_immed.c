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
typedef  int u16 ;
typedef  enum immed_shift { ____Placeholder_immed_shift } immed_shift ;

/* Variables and functions */
 int IMMED_SHIFT_0B ; 
 int IMMED_SHIFT_1B ; 
 int IMMED_SHIFT_2B ; 

__attribute__((used)) static bool pack_immed(u32 imm, u16 *val, enum immed_shift *shift)
{
	if (!(imm & 0xffff0000)) {
		*val = imm;
		*shift = IMMED_SHIFT_0B;
	} else if (!(imm & 0xff0000ff)) {
		*val = imm >> 8;
		*shift = IMMED_SHIFT_1B;
	} else if (!(imm & 0x0000ffff)) {
		*val = imm >> 16;
		*shift = IMMED_SHIFT_2B;
	} else {
		return false;
	}

	return true;
}