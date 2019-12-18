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
typedef  int u32 ;
struct max77693_led_device {scalar_t__ iout_joint; } ;

/* Variables and functions */
 size_t FLED1 ; 
 size_t FLED2 ; 
 int /*<<< orphan*/  clamp_align (int*,int,int,int) ; 
 scalar_t__ max77693_fled_used (struct max77693_led_device*,int) ; 

__attribute__((used)) static void max77693_align_iout_current(struct max77693_led_device *led,
					u32 *iout, u32 min, u32 max, u32 step)
{
	int i;

	if (led->iout_joint) {
		if (iout[FLED1] > min) {
			iout[FLED1] /= 2;
			iout[FLED2] = iout[FLED1];
		} else {
			iout[FLED1] = min;
			iout[FLED2] = 0;
			return;
		}
	}

	for (i = FLED1; i <= FLED2; ++i)
		if (max77693_fled_used(led, i))
			clamp_align(&iout[i], min, max, step);
		else
			iout[i] = 0;
}