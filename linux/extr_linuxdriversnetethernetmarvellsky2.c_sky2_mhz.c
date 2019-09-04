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
struct sky2_hw {int chip_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CHIP_ID_YUKON_EC 138 
#define  CHIP_ID_YUKON_EC_U 137 
#define  CHIP_ID_YUKON_EX 136 
#define  CHIP_ID_YUKON_FE 135 
#define  CHIP_ID_YUKON_FE_P 134 
#define  CHIP_ID_YUKON_OPT 133 
#define  CHIP_ID_YUKON_OP_2 132 
#define  CHIP_ID_YUKON_PRM 131 
#define  CHIP_ID_YUKON_SUPR 130 
#define  CHIP_ID_YUKON_UL_2 129 
#define  CHIP_ID_YUKON_XL 128 

__attribute__((used)) static u32 sky2_mhz(const struct sky2_hw *hw)
{
	switch (hw->chip_id) {
	case CHIP_ID_YUKON_EC:
	case CHIP_ID_YUKON_EC_U:
	case CHIP_ID_YUKON_EX:
	case CHIP_ID_YUKON_SUPR:
	case CHIP_ID_YUKON_UL_2:
	case CHIP_ID_YUKON_OPT:
	case CHIP_ID_YUKON_PRM:
	case CHIP_ID_YUKON_OP_2:
		return 125;

	case CHIP_ID_YUKON_FE:
		return 100;

	case CHIP_ID_YUKON_FE_P:
		return 50;

	case CHIP_ID_YUKON_XL:
		return 156;

	default:
		BUG();
	}
}