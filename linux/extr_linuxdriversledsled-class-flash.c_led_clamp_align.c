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
struct led_flash_setting {int val; int step; int min; int /*<<< orphan*/  max; } ;

/* Variables and functions */
 int clamp (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void led_clamp_align(struct led_flash_setting *s)
{
	u32 v, offset;

	v = s->val + s->step / 2;
	v = clamp(v, s->min, s->max);
	offset = v - s->min;
	offset = s->step * (offset / s->step);
	s->val = s->min + offset;
}