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
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int GPIOD_FLAGS_BIT_DIR_OUT ; 
 TYPE_1__* mctrl_gpios_desc ; 

__attribute__((used)) static bool mctrl_gpio_flags_is_dir_out(unsigned int idx)
{
	return mctrl_gpios_desc[idx].flags & GPIOD_FLAGS_BIT_DIR_OUT;
}