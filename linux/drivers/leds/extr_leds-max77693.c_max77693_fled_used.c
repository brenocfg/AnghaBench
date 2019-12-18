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
struct max77693_led_device {int fled_mask; } ;

/* Variables and functions */
 int FLED1 ; 
 int FLED1_IOUT ; 
 int FLED2_IOUT ; 

__attribute__((used)) static inline bool max77693_fled_used(struct max77693_led_device *led,
					 int fled_id)
{
	u8 fled_bit = (fled_id == FLED1) ? FLED1_IOUT : FLED2_IOUT;

	return led->fled_mask & fled_bit;
}