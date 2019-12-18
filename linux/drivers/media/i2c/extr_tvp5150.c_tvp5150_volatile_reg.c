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
struct device {int dummy; } ;

/* Variables and functions */
#define  TVP5150_FIFO_WORD_COUNT 140 
#define  TVP5150_INT_ACTIVE_REG_B 139 
#define  TVP5150_INT_STATUS_REG_A 138 
#define  TVP5150_INT_STATUS_REG_B 137 
#define  TVP5150_STATUS_REG_1 136 
#define  TVP5150_STATUS_REG_2 135 
#define  TVP5150_STATUS_REG_3 134 
#define  TVP5150_STATUS_REG_4 133 
#define  TVP5150_STATUS_REG_5 132 
#define  TVP5150_VBI_FIFO_READ_DATA 131 
#define  TVP5150_VDP_STATUS_REG 130 
#define  TVP5150_VERT_LN_COUNT_LSB 129 
#define  TVP5150_VERT_LN_COUNT_MSB 128 

__attribute__((used)) static bool tvp5150_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case TVP5150_VERT_LN_COUNT_MSB:
	case TVP5150_VERT_LN_COUNT_LSB:
	case TVP5150_INT_STATUS_REG_A:
	case TVP5150_INT_STATUS_REG_B:
	case TVP5150_INT_ACTIVE_REG_B:
	case TVP5150_STATUS_REG_1:
	case TVP5150_STATUS_REG_2:
	case TVP5150_STATUS_REG_3:
	case TVP5150_STATUS_REG_4:
	case TVP5150_STATUS_REG_5:
	/* CC, WSS, VPS, VITC data? */
	case TVP5150_VBI_FIFO_READ_DATA:
	case TVP5150_VDP_STATUS_REG:
	case TVP5150_FIFO_WORD_COUNT:
		return true;
	default:
		return false;
	}
}