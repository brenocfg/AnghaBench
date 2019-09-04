#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct led_classdev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct apu_led_priv {TYPE_1__ param; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  APU1_LEDOFF ; 
 int /*<<< orphan*/  APU1_LEDON ; 
 TYPE_2__* apu_led ; 
 struct apu_led_priv* cdev_to_priv (struct led_classdev*) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void apu1_led_brightness_set(struct led_classdev *led, enum led_brightness value)
{
	struct apu_led_priv *pled = cdev_to_priv(led);

	spin_lock(&apu_led->lock);
	iowrite8(value ? APU1_LEDON : APU1_LEDOFF, pled->param.addr);
	spin_unlock(&apu_led->lock);
}