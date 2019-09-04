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
typedef  unsigned int const s32 ;

/* Variables and functions */
 unsigned int const PAC7302_RGB_BALANCE_MAX ; 
 unsigned int const PAC7302_RGB_BALANCE_MIN ; 

__attribute__((used)) static u8 rgbbalance_ctrl_to_reg_value(s32 rgb_ctrl_val)
{
	const unsigned int k = 1000;	/* precision factor */
	unsigned int norm;

	/* Normed value [0...k] */
	norm = k * (rgb_ctrl_val - PAC7302_RGB_BALANCE_MIN)
		    / (PAC7302_RGB_BALANCE_MAX - PAC7302_RGB_BALANCE_MIN);
	/* Qudratic apporach improves control at small (register) values: */
	return 64 * norm * norm / (k*k)  +  32 * norm / k  +  32;
	/* Y = 64*X*X + 32*X + 32
	 * => register values 0x20-0x80; Windows driver uses these limits */

	/* NOTE: for full value range (0x00-0xff) use
	 *         Y = 254*X*X + X
	 *         => 254 * norm * norm / (k*k)  +  1 * norm / k	*/
}