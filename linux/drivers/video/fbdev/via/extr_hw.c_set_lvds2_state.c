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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  VIASR ; 
#define  VIA_STATE_OFF 129 
#define  VIA_STATE_ON 128 
 int /*<<< orphan*/  via_write_reg_mask (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void set_lvds2_state(u8 state)
{
	u8 value;

	switch (state) {
	case VIA_STATE_ON:
		value = 0x0C;
		break;
	case VIA_STATE_OFF:
		value = 0x00;
		break;
	default:
		return;
	}

	via_write_reg_mask(VIASR, 0x2A, value, 0x0C);
}