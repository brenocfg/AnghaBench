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
typedef  int u16 ;
struct bmc150_magn_trim_regs {scalar_t__ y1; scalar_t__ y2; scalar_t__ xy1; scalar_t__ xy2; int /*<<< orphan*/  xyz1; } ;
typedef  int s32 ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 scalar_t__ BMC150_MAGN_XY_OVERFLOW_VAL ; 
 int S32_MIN ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 bmc150_magn_compensate_y(struct bmc150_magn_trim_regs *tregs, s16 y,
				    u16 rhall)
{
	s16 val;
	u16 xyz1 = le16_to_cpu(tregs->xyz1);

	if (y == BMC150_MAGN_XY_OVERFLOW_VAL)
		return S32_MIN;

	if (!rhall)
		rhall = xyz1;

	val = ((s16)(((u16)((((s32)xyz1) << 14) / rhall)) - ((u16)0x4000)));
	val = ((s16)((((s32)y) * ((((((((s32)tregs->xy2) * ((((s32)val) *
	      ((s32)val)) >> 7)) + (((s32)val) *
	      ((s32)(((s16)tregs->xy1) << 7)))) >> 9) + ((s32)0x100000)) *
	      ((s32)(((s16)tregs->y2) + ((s16)0xA0)))) >> 12)) >> 13)) +
	      (((s16)tregs->y1) << 3);

	return (s32)val;
}