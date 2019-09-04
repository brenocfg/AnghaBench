#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sc27xx_led {int line; TYPE_1__* priv; } ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 int SC27XX_LEDS_OFFSET ; 

__attribute__((used)) static u32 sc27xx_led_get_offset(struct sc27xx_led *leds)
{
	return leds->priv->base + SC27XX_LEDS_OFFSET * leds->line;
}