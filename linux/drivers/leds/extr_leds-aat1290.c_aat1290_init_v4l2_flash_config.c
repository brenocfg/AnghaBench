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
struct v4l2_flash_config {int dummy; } ;
struct aat1290_led_config_data {int dummy; } ;
struct aat1290_led {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void aat1290_init_v4l2_flash_config(struct aat1290_led *led,
				struct aat1290_led_config_data *led_cfg,
				struct v4l2_flash_config *v4l2_sd_cfg)
{
}