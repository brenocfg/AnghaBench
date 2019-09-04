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
struct is31fl32xx_priv {int dummy; } ;
struct is31fl32xx_led_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline size_t sizeof_is31fl32xx_priv(int num_leds)
{
	return sizeof(struct is31fl32xx_priv) +
		      (sizeof(struct is31fl32xx_led_data) * num_leds);
}