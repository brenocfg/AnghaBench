#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_11__ {int brightness; } ;
struct TYPE_12__ {TYPE_5__ cdev; } ;
struct TYPE_9__ {int brightness; } ;
struct TYPE_10__ {TYPE_3__ cdev; } ;
struct TYPE_7__ {int brightness; } ;
struct TYPE_8__ {TYPE_1__ cdev; } ;
struct hidled_rgb {TYPE_6__ blue; TYPE_4__ green; TYPE_2__ red; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int /*<<< orphan*/  RISO_KAGAKU_IX (int,int,int) ; 
 scalar_t__ riso_kagaku_switch_green_blue ; 

__attribute__((used)) static u8 riso_kagaku_index(struct hidled_rgb *rgb)
{
	enum led_brightness r, g, b;

	r = rgb->red.cdev.brightness;
	g = rgb->green.cdev.brightness;
	b = rgb->blue.cdev.brightness;

	if (riso_kagaku_switch_green_blue)
		return RISO_KAGAKU_IX(r, b, g);
	else
		return RISO_KAGAKU_IX(r, g, b);
}