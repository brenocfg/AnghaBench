#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {void* max_brightness; } ;
struct max8997_led {int led_mode; TYPE_2__* iodev; TYPE_1__ cdev; int /*<<< orphan*/  id; } ;
struct i2c_client {int dummy; } ;
typedef  enum max8997_led_mode { ____Placeholder_max8997_led_mode } max8997_led_mode ;
struct TYPE_4__ {int /*<<< orphan*/  dev; struct i2c_client* i2c; } ;

/* Variables and functions */
#define  MAX8997_FLASH_MODE 131 
#define  MAX8997_FLASH_PIN_CONTROL_MODE 130 
 int MAX8997_LED0_FLASH_MASK ; 
 int MAX8997_LED0_FLASH_PIN_MASK ; 
 int MAX8997_LED0_MOVIE_MASK ; 
 int MAX8997_LED0_MOVIE_PIN_MASK ; 
 int MAX8997_LED1_FLASH_MASK ; 
 int MAX8997_LED1_FLASH_PIN_MASK ; 
 int MAX8997_LED1_MOVIE_MASK ; 
 int MAX8997_LED1_MOVIE_PIN_MASK ; 
 void* MAX8997_LED_FLASH_MAX_BRIGHTNESS ; 
 void* MAX8997_LED_MOVIE_MAX_BRIGHTNESS ; 
 void* MAX8997_LED_NONE_MAX_BRIGHTNESS ; 
#define  MAX8997_MOVIE_MODE 129 
#define  MAX8997_MOVIE_PIN_CONTROL_MODE 128 
 int /*<<< orphan*/  MAX8997_REG_LEN_CNTL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int max8997_update_reg (struct i2c_client*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void max8997_led_set_mode(struct max8997_led *led,
			enum max8997_led_mode mode)
{
	int ret;
	struct i2c_client *client = led->iodev->i2c;
	u8 mask = 0, val;

	switch (mode) {
	case MAX8997_FLASH_MODE:
		mask = MAX8997_LED1_FLASH_MASK | MAX8997_LED0_FLASH_MASK;
		val = led->id ?
		      MAX8997_LED1_FLASH_MASK : MAX8997_LED0_FLASH_MASK;
		led->cdev.max_brightness = MAX8997_LED_FLASH_MAX_BRIGHTNESS;
		break;
	case MAX8997_MOVIE_MODE:
		mask = MAX8997_LED1_MOVIE_MASK | MAX8997_LED0_MOVIE_MASK;
		val = led->id ?
		      MAX8997_LED1_MOVIE_MASK : MAX8997_LED0_MOVIE_MASK;
		led->cdev.max_brightness = MAX8997_LED_MOVIE_MAX_BRIGHTNESS;
		break;
	case MAX8997_FLASH_PIN_CONTROL_MODE:
		mask = MAX8997_LED1_FLASH_PIN_MASK |
		       MAX8997_LED0_FLASH_PIN_MASK;
		val = led->id ?
		      MAX8997_LED1_FLASH_PIN_MASK : MAX8997_LED0_FLASH_PIN_MASK;
		led->cdev.max_brightness = MAX8997_LED_FLASH_MAX_BRIGHTNESS;
		break;
	case MAX8997_MOVIE_PIN_CONTROL_MODE:
		mask = MAX8997_LED1_MOVIE_PIN_MASK |
		       MAX8997_LED0_MOVIE_PIN_MASK;
		val = led->id ?
		      MAX8997_LED1_MOVIE_PIN_MASK : MAX8997_LED0_MOVIE_PIN_MASK;
		led->cdev.max_brightness = MAX8997_LED_MOVIE_MAX_BRIGHTNESS;
		break;
	default:
		led->cdev.max_brightness = MAX8997_LED_NONE_MAX_BRIGHTNESS;
		break;
	}

	if (mask) {
		ret = max8997_update_reg(client, MAX8997_REG_LEN_CNTL, val,
					 mask);
		if (ret)
			dev_err(led->iodev->dev,
				"failed to update register(%d)\n", ret);
	}

	led->led_mode = mode;
}