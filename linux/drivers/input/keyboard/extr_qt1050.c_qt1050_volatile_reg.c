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
#define  QT1050_DET_STATUS 139 
#define  QT1050_KEY_SIGNAL_0_LSB 138 
#define  QT1050_KEY_SIGNAL_0_MSB 137 
#define  QT1050_KEY_SIGNAL_1_LSB 136 
#define  QT1050_KEY_SIGNAL_1_MSB 135 
#define  QT1050_KEY_SIGNAL_2_LSB 134 
#define  QT1050_KEY_SIGNAL_2_MSB 133 
#define  QT1050_KEY_SIGNAL_3_LSB 132 
#define  QT1050_KEY_SIGNAL_3_MSB 131 
#define  QT1050_KEY_SIGNAL_4_LSB 130 
#define  QT1050_KEY_SIGNAL_4_MSB 129 
#define  QT1050_KEY_STATUS 128 

__attribute__((used)) static bool qt1050_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case QT1050_DET_STATUS:
	case QT1050_KEY_STATUS:
	case QT1050_KEY_SIGNAL_0_MSB:
	case QT1050_KEY_SIGNAL_0_LSB:
	case QT1050_KEY_SIGNAL_1_MSB:
	case QT1050_KEY_SIGNAL_1_LSB:
	case QT1050_KEY_SIGNAL_2_MSB:
	case QT1050_KEY_SIGNAL_2_LSB:
	case QT1050_KEY_SIGNAL_3_MSB:
	case QT1050_KEY_SIGNAL_3_LSB:
	case QT1050_KEY_SIGNAL_4_MSB:
	case QT1050_KEY_SIGNAL_4_LSB:
		return true;
	default:
		return false;
	}
}