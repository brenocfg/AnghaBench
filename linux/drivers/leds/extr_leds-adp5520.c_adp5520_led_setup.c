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
struct adp5520_led {int flags; int id; struct device* master; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADP5520_C3_MODE ; 
 int ADP5520_FLAG_OFFT_MASK ; 
 int ADP5520_FLAG_OFFT_SHIFT ; 
 int ADP5520_LED1_EN ; 
 int ADP5520_LED2_EN ; 
 int ADP5520_LED3_EN ; 
 int /*<<< orphan*/  ADP5520_LED_CONTROL ; 
 int /*<<< orphan*/  ADP5520_LED_TIME ; 
 int /*<<< orphan*/  ADP5520_R3_MODE ; 
#define  FLAG_ID_ADP5520_LED1_ADP5501_LED0 130 
#define  FLAG_ID_ADP5520_LED2_ADP5501_LED1 129 
#define  FLAG_ID_ADP5520_LED3_ADP5501_LED2 128 
 int adp5520_clr_bits (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int adp5520_set_bits (struct device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int adp5520_led_setup(struct adp5520_led *led)
{
	struct device *dev = led->master;
	int flags = led->flags;
	int ret = 0;

	switch (led->id) {
	case FLAG_ID_ADP5520_LED1_ADP5501_LED0:
		ret |= adp5520_set_bits(dev, ADP5520_LED_TIME,
					(flags >> ADP5520_FLAG_OFFT_SHIFT) &
					ADP5520_FLAG_OFFT_MASK);
		ret |= adp5520_set_bits(dev, ADP5520_LED_CONTROL,
					ADP5520_LED1_EN);
		break;
	case FLAG_ID_ADP5520_LED2_ADP5501_LED1:
		ret |= adp5520_set_bits(dev,  ADP5520_LED_TIME,
					((flags >> ADP5520_FLAG_OFFT_SHIFT) &
					ADP5520_FLAG_OFFT_MASK) << 2);
		ret |= adp5520_clr_bits(dev, ADP5520_LED_CONTROL,
					 ADP5520_R3_MODE);
		ret |= adp5520_set_bits(dev, ADP5520_LED_CONTROL,
					ADP5520_LED2_EN);
		break;
	case FLAG_ID_ADP5520_LED3_ADP5501_LED2:
		ret |= adp5520_set_bits(dev,  ADP5520_LED_TIME,
					((flags >> ADP5520_FLAG_OFFT_SHIFT) &
					ADP5520_FLAG_OFFT_MASK) << 4);
		ret |= adp5520_clr_bits(dev, ADP5520_LED_CONTROL,
					ADP5520_C3_MODE);
		ret |= adp5520_set_bits(dev, ADP5520_LED_CONTROL,
					ADP5520_LED3_EN);
		break;
	}

	return ret;
}