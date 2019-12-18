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
#define  LM95245_REG_RW_COMMON_HYSTERESIS 137 
#define  LM95245_REG_RW_CONFIG1 136 
#define  LM95245_REG_RW_CONFIG2 135 
#define  LM95245_REG_RW_CONVERS_RATE 134 
#define  LM95245_REG_RW_LOCAL_OS_TCRIT_LIMIT 133 
#define  LM95245_REG_RW_REMOTE_OFFH 132 
#define  LM95245_REG_RW_REMOTE_OFFL 131 
#define  LM95245_REG_RW_REMOTE_OS_LIMIT 130 
#define  LM95245_REG_RW_REMOTE_TCRIT_LIMIT 129 
#define  LM95245_REG_W_ONE_SHOT 128 

__attribute__((used)) static bool lm95245_is_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case LM95245_REG_RW_CONFIG1:
	case LM95245_REG_RW_CONVERS_RATE:
	case LM95245_REG_W_ONE_SHOT:
	case LM95245_REG_RW_CONFIG2:
	case LM95245_REG_RW_REMOTE_OFFH:
	case LM95245_REG_RW_REMOTE_OFFL:
	case LM95245_REG_RW_REMOTE_OS_LIMIT:
	case LM95245_REG_RW_LOCAL_OS_TCRIT_LIMIT:
	case LM95245_REG_RW_REMOTE_TCRIT_LIMIT:
	case LM95245_REG_RW_COMMON_HYSTERESIS:
		return true;
	default:
		return false;
	}
}