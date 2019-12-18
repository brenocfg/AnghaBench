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
struct psb_intel_i2c_chan {int /*<<< orphan*/  reg; struct drm_device* drm_dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int GPIO_CLOCK_PULLUP_DISABLE ; 
 int GPIO_DATA_DIR_IN ; 
 int GPIO_DATA_DIR_MASK ; 
 int GPIO_DATA_DIR_OUT ; 
 int GPIO_DATA_PULLUP_DISABLE ; 
 int GPIO_DATA_VAL_MASK ; 
 int /*<<< orphan*/  I2C_RISEFALL_TIME ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_data(void *data, int state_high)
{
	struct psb_intel_i2c_chan *chan = data;
	struct drm_device *dev = chan->drm_dev;
	u32 reserved = 0, data_bits;

	/* On most chips, these bits must be preserved in software. */
	reserved =
		    REG_READ(chan->reg) & (GPIO_DATA_PULLUP_DISABLE |
					   GPIO_CLOCK_PULLUP_DISABLE);

	if (state_high)
		data_bits = GPIO_DATA_DIR_IN | GPIO_DATA_DIR_MASK;
	else
		data_bits =
		    GPIO_DATA_DIR_OUT | GPIO_DATA_DIR_MASK |
		    GPIO_DATA_VAL_MASK;

	REG_WRITE(chan->reg, reserved | data_bits);
	udelay(I2C_RISEFALL_TIME);	/* wait for the line to change state */
}