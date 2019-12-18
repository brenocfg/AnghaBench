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
typedef  int /*<<< orphan*/  u32 ;
struct max77693_led_device {int iout_joint; } ;
struct max77693_led_config_data {scalar_t__ boost_mode; int num_leds; scalar_t__ low_vsys; scalar_t__ boost_vout; scalar_t__* flash_timeout_max; int /*<<< orphan*/  iout_flash_max; int /*<<< orphan*/  iout_torch_max; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  FLASH_IOUT_MAX_1LED ; 
 int /*<<< orphan*/  FLASH_IOUT_MAX_2LEDS ; 
 int /*<<< orphan*/  FLASH_IOUT_MIN ; 
 int /*<<< orphan*/  FLASH_IOUT_STEP ; 
 int /*<<< orphan*/  FLASH_TIMEOUT_MAX ; 
 int /*<<< orphan*/  FLASH_TIMEOUT_MIN ; 
 int /*<<< orphan*/  FLASH_TIMEOUT_STEP ; 
 int /*<<< orphan*/  FLASH_VOUT_MAX ; 
 int /*<<< orphan*/  FLASH_VOUT_MIN ; 
 int /*<<< orphan*/  FLASH_VOUT_STEP ; 
 int /*<<< orphan*/  FLED1 ; 
 int /*<<< orphan*/  FLED2 ; 
 scalar_t__ MAX77693_LED_BOOST_FIXED ; 
 scalar_t__ MAX77693_LED_BOOST_NONE ; 
 int /*<<< orphan*/  MAX_FLASH1_VSYS_MAX ; 
 int /*<<< orphan*/  MAX_FLASH1_VSYS_MIN ; 
 int /*<<< orphan*/  MAX_FLASH1_VSYS_STEP ; 
 int /*<<< orphan*/  TORCH_IOUT_MAX ; 
 int /*<<< orphan*/  TORCH_IOUT_MIN ; 
 int /*<<< orphan*/  TORCH_IOUT_STEP ; 
 int /*<<< orphan*/  clamp_align (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ clamp_val (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  max77693_align_iout_current (struct max77693_led_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ max77693_fled_used (struct max77693_led_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max77693_led_validate_configuration(struct max77693_led_device *led,
					struct max77693_led_config_data *cfg)
{
	u32 flash_iout_max = cfg->boost_mode ? FLASH_IOUT_MAX_2LEDS :
					       FLASH_IOUT_MAX_1LED;
	int i;

	if (cfg->num_leds == 1 &&
	    max77693_fled_used(led, FLED1) && max77693_fled_used(led, FLED2))
		led->iout_joint = true;

	cfg->boost_mode = clamp_val(cfg->boost_mode, MAX77693_LED_BOOST_NONE,
			    MAX77693_LED_BOOST_FIXED);

	/* Boost must be enabled if both current outputs are used */
	if ((cfg->boost_mode == MAX77693_LED_BOOST_NONE) && led->iout_joint)
		cfg->boost_mode = MAX77693_LED_BOOST_FIXED;

	max77693_align_iout_current(led, cfg->iout_torch_max,
			TORCH_IOUT_MIN, TORCH_IOUT_MAX, TORCH_IOUT_STEP);

	max77693_align_iout_current(led, cfg->iout_flash_max,
			FLASH_IOUT_MIN, flash_iout_max, FLASH_IOUT_STEP);

	for (i = 0; i < ARRAY_SIZE(cfg->flash_timeout_max); ++i)
		clamp_align(&cfg->flash_timeout_max[i], FLASH_TIMEOUT_MIN,
				FLASH_TIMEOUT_MAX, FLASH_TIMEOUT_STEP);

	clamp_align(&cfg->boost_vout, FLASH_VOUT_MIN, FLASH_VOUT_MAX,
							FLASH_VOUT_STEP);

	if (cfg->low_vsys)
		clamp_align(&cfg->low_vsys, MAX_FLASH1_VSYS_MIN,
				MAX_FLASH1_VSYS_MAX, MAX_FLASH1_VSYS_STEP);
}