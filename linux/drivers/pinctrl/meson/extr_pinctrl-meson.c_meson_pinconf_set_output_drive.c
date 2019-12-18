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
struct meson_pinctrl {int dummy; } ;

/* Variables and functions */
 int meson_pinconf_set_drive (struct meson_pinctrl*,unsigned int,int) ; 
 int meson_pinconf_set_output (struct meson_pinctrl*,unsigned int,int) ; 

__attribute__((used)) static int meson_pinconf_set_output_drive(struct meson_pinctrl *pc,
					  unsigned int pin,
					  bool high)
{
	int ret;

	ret = meson_pinconf_set_output(pc, pin, true);
	if (ret)
		return ret;

	return meson_pinconf_set_drive(pc, pin, high);
}