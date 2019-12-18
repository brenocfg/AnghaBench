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
typedef  void* u16 ;
struct bmc150_magn_trim_regs {int /*<<< orphan*/  z4; int /*<<< orphan*/  z3; int /*<<< orphan*/  z2; int /*<<< orphan*/  z1; int /*<<< orphan*/  xyz1; } ;
typedef  int s32 ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 scalar_t__ BMC150_MAGN_Z_OVERFLOW_VAL ; 
 int S32_MIN ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 bmc150_magn_compensate_z(struct bmc150_magn_trim_regs *tregs, s16 z,
				    u16 rhall)
{
	s32 val;
	u16 xyz1 = le16_to_cpu(tregs->xyz1);
	u16 z1 = le16_to_cpu(tregs->z1);
	s16 z2 = le16_to_cpu(tregs->z2);
	s16 z3 = le16_to_cpu(tregs->z3);
	s16 z4 = le16_to_cpu(tregs->z4);

	if (z == BMC150_MAGN_Z_OVERFLOW_VAL)
		return S32_MIN;

	val = (((((s32)(z - z4)) << 15) - ((((s32)z3) * ((s32)(((s16)rhall) -
	      ((s16)xyz1)))) >> 2)) / (z2 + ((s16)(((((s32)z1) *
	      ((((s16)rhall) << 1))) + (1 << 15)) >> 16))));

	return val;
}