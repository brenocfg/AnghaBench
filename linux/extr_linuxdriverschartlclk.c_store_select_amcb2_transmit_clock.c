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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  CLK_11_184MHz 131 
 unsigned char CLK_16_384MHz ; 
#define  CLK_34_368MHz 130 
#define  CLK_44_736MHz 129 
#define  CLK_8_592MHz 128 
 unsigned char CLK_8kHz ; 
 int /*<<< orphan*/  SET_PORT_BITS (int /*<<< orphan*/ ,int,unsigned char) ; 
 int /*<<< orphan*/  TLCLK_REG0 ; 
 int /*<<< orphan*/  TLCLK_REG1 ; 
 int /*<<< orphan*/  TLCLK_REG3 ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned long) ; 
 int /*<<< orphan*/  event_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,unsigned long*) ; 
 int /*<<< orphan*/  strnlen (char const*,size_t) ; 

__attribute__((used)) static ssize_t store_select_amcb2_transmit_clock(struct device *d,
		struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned long flags;
	unsigned long tmp;
	unsigned char val;

	sscanf(buf, "%lX", &tmp);
	dev_dbg(d, "tmp = 0x%lX\n", tmp);

	val = (unsigned char)tmp;
	spin_lock_irqsave(&event_lock, flags);
		if ((val == CLK_8kHz) || (val == CLK_16_384MHz)) {
			SET_PORT_BITS(TLCLK_REG3, 0xc7, 0x28);
			SET_PORT_BITS(TLCLK_REG1, 0xfb, ~val);
		} else if (val >= CLK_8_592MHz) {
			SET_PORT_BITS(TLCLK_REG3, 0xc7, 0x38);
			switch (val) {
			case CLK_8_592MHz:
				SET_PORT_BITS(TLCLK_REG0, 0xfc, 2);
				break;
			case CLK_11_184MHz:
				SET_PORT_BITS(TLCLK_REG0, 0xfc, 0);
				break;
			case CLK_34_368MHz:
				SET_PORT_BITS(TLCLK_REG0, 0xfc, 3);
				break;
			case CLK_44_736MHz:
				SET_PORT_BITS(TLCLK_REG0, 0xfc, 1);
				break;
			}
		} else
			SET_PORT_BITS(TLCLK_REG3, 0xc7, val << 3);

	spin_unlock_irqrestore(&event_lock, flags);

	return strnlen(buf, count);
}