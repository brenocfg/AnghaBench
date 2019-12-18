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
typedef  int u8 ;
typedef  enum led_ids { ____Placeholder_led_ids } led_ids ;
typedef  enum led_colors { ____Placeholder_led_colors } led_colors ;

/* Variables and functions */
 int BD2802_COLOR_OFFSET ; 
 int BD2802_LED_OFFSET ; 

__attribute__((used)) static inline u8 bd2802_get_base_offset(enum led_ids id, enum led_colors color)
{
	return id * BD2802_LED_OFFSET + color * BD2802_COLOR_OFFSET;
}