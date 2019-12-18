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
#define  LP8788_BUCK1_VOUT0 135 
#define  LP8788_BUCK1_VOUT1 134 
#define  LP8788_BUCK1_VOUT2 133 
#define  LP8788_BUCK1_VOUT3 132 
#define  LP8788_BUCK2_VOUT0 131 
#define  LP8788_BUCK2_VOUT1 130 
#define  LP8788_BUCK2_VOUT2 129 
#define  LP8788_BUCK2_VOUT3 128 

__attribute__((used)) static bool lp8788_is_valid_buck_addr(u8 addr)
{
	switch (addr) {
	case LP8788_BUCK1_VOUT0:
	case LP8788_BUCK1_VOUT1:
	case LP8788_BUCK1_VOUT2:
	case LP8788_BUCK1_VOUT3:
	case LP8788_BUCK2_VOUT0:
	case LP8788_BUCK2_VOUT1:
	case LP8788_BUCK2_VOUT2:
	case LP8788_BUCK2_VOUT3:
		return true;
	default:
		return false;
	}
}