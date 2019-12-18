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

/* Variables and functions */
 int EINVAL ; 
#define  TPS65910_REG_VDD1 140 
#define  TPS65910_REG_VDD2 139 
#define  TPS65910_REG_VIO 138 
#define  TPS65910_REG_VRTC 137 
 int TPS65910_VDD1 ; 
 int TPS65910_VDD2 ; 
 int TPS65910_VIO ; 
 int TPS65910_VRTC ; 
 int TPS65911_LDO1 ; 
 int TPS65911_LDO2 ; 
 int TPS65911_LDO3 ; 
 int TPS65911_LDO4 ; 
 int TPS65911_LDO5 ; 
 int TPS65911_LDO6 ; 
 int TPS65911_LDO7 ; 
 int TPS65911_LDO8 ; 
#define  TPS65911_REG_LDO1 136 
#define  TPS65911_REG_LDO2 135 
#define  TPS65911_REG_LDO3 134 
#define  TPS65911_REG_LDO4 133 
#define  TPS65911_REG_LDO5 132 
#define  TPS65911_REG_LDO6 131 
#define  TPS65911_REG_LDO7 130 
#define  TPS65911_REG_LDO8 129 
#define  TPS65911_REG_VDDCTRL 128 
 int TPS65911_VDDCTRL ; 

__attribute__((used)) static int tps65911_get_ctrl_register(int id)
{
	switch (id) {
	case TPS65910_REG_VRTC:
		return TPS65910_VRTC;
	case TPS65910_REG_VIO:
		return TPS65910_VIO;
	case TPS65910_REG_VDD1:
		return TPS65910_VDD1;
	case TPS65910_REG_VDD2:
		return TPS65910_VDD2;
	case TPS65911_REG_VDDCTRL:
		return TPS65911_VDDCTRL;
	case TPS65911_REG_LDO1:
		return TPS65911_LDO1;
	case TPS65911_REG_LDO2:
		return TPS65911_LDO2;
	case TPS65911_REG_LDO3:
		return TPS65911_LDO3;
	case TPS65911_REG_LDO4:
		return TPS65911_LDO4;
	case TPS65911_REG_LDO5:
		return TPS65911_LDO5;
	case TPS65911_REG_LDO6:
		return TPS65911_LDO6;
	case TPS65911_REG_LDO7:
		return TPS65911_LDO7;
	case TPS65911_REG_LDO8:
		return TPS65911_LDO8;
	default:
		return -EINVAL;
	}
}