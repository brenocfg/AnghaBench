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
#define  MAX6621_CONFIG0_REG 145 
#define  MAX6621_CONFIG1_REG 144 
#define  MAX6621_CONFIG2_REG 143 
#define  MAX6621_CONFIG3_REG 142 
#define  MAX6621_TEMP_MAX_ADDR_REG 141 
#define  MAX6621_TEMP_MAX_REG 140 
#define  MAX6621_TEMP_S0D0_REG 139 
#define  MAX6621_TEMP_S0D1_REG 138 
#define  MAX6621_TEMP_S0_ALERT_REG 137 
#define  MAX6621_TEMP_S1D0_REG 136 
#define  MAX6621_TEMP_S1D1_REG 135 
#define  MAX6621_TEMP_S1_ALERT_REG 134 
#define  MAX6621_TEMP_S2D0_REG 133 
#define  MAX6621_TEMP_S2D1_REG 132 
#define  MAX6621_TEMP_S2_ALERT_REG 131 
#define  MAX6621_TEMP_S3D0_REG 130 
#define  MAX6621_TEMP_S3D1_REG 129 
#define  MAX6621_TEMP_S3_ALERT_REG 128 

__attribute__((used)) static bool max6621_readable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case MAX6621_TEMP_S0D0_REG:
	case MAX6621_TEMP_S0D1_REG:
	case MAX6621_TEMP_S1D0_REG:
	case MAX6621_TEMP_S1D1_REG:
	case MAX6621_TEMP_S2D0_REG:
	case MAX6621_TEMP_S2D1_REG:
	case MAX6621_TEMP_S3D0_REG:
	case MAX6621_TEMP_S3D1_REG:
	case MAX6621_TEMP_MAX_REG:
	case MAX6621_TEMP_MAX_ADDR_REG:
	case MAX6621_CONFIG0_REG:
	case MAX6621_CONFIG1_REG:
	case MAX6621_CONFIG2_REG:
	case MAX6621_CONFIG3_REG:
	case MAX6621_TEMP_S0_ALERT_REG:
	case MAX6621_TEMP_S1_ALERT_REG:
	case MAX6621_TEMP_S2_ALERT_REG:
	case MAX6621_TEMP_S3_ALERT_REG:
		return true;
	}
	return false;
}