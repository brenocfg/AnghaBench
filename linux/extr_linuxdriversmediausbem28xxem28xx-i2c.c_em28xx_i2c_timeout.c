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
struct em28xx {int i2c_speed; } ;

/* Variables and functions */
#define  EM28XX_I2C_FREQ_100_KHZ 130 
#define  EM28XX_I2C_FREQ_25_KHZ 129 
#define  EM28XX_I2C_FREQ_400_KHZ 128 
 int EM28XX_I2C_XFER_TIMEOUT ; 
 int msecs_to_jiffies (int) ; 

__attribute__((used)) static int em28xx_i2c_timeout(struct em28xx *dev)
{
	int time = EM28XX_I2C_XFER_TIMEOUT;

	switch (dev->i2c_speed & 0x03) {
	case EM28XX_I2C_FREQ_25_KHZ:
		time += 4;		/* Assume 4 ms for transfers */
		break;
	case EM28XX_I2C_FREQ_100_KHZ:
	case EM28XX_I2C_FREQ_400_KHZ:
		time += 1;		/* Assume 1 ms for transfers */
		break;
	default: /* EM28XX_I2C_FREQ_1_5_MHZ */
		break;
	}

	return msecs_to_jiffies(time);
}