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
#define  LM95245_REG_R_LOCAL_TEMPH_S 135 
#define  LM95245_REG_R_LOCAL_TEMPL_S 134 
#define  LM95245_REG_R_REMOTE_TEMPH_S 133 
#define  LM95245_REG_R_REMOTE_TEMPH_U 132 
#define  LM95245_REG_R_REMOTE_TEMPL_S 131 
#define  LM95245_REG_R_REMOTE_TEMPL_U 130 
#define  LM95245_REG_R_STATUS1 129 
#define  LM95245_REG_R_STATUS2 128 

__attribute__((used)) static bool lm95245_is_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case LM95245_REG_R_STATUS1:
	case LM95245_REG_R_STATUS2:
	case LM95245_REG_R_LOCAL_TEMPH_S:
	case LM95245_REG_R_LOCAL_TEMPL_S:
	case LM95245_REG_R_REMOTE_TEMPH_S:
	case LM95245_REG_R_REMOTE_TEMPL_S:
	case LM95245_REG_R_REMOTE_TEMPH_U:
	case LM95245_REG_R_REMOTE_TEMPL_U:
		return true;
	default:
		return false;
	}
}