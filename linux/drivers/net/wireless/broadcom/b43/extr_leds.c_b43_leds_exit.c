#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct b43_wldev {TYPE_4__* wl; } ;
struct TYPE_8__ {int /*<<< orphan*/  activelow; int /*<<< orphan*/  index; } ;
struct TYPE_7__ {int /*<<< orphan*/  activelow; int /*<<< orphan*/  index; } ;
struct TYPE_6__ {int /*<<< orphan*/  activelow; int /*<<< orphan*/  index; } ;
struct TYPE_10__ {int /*<<< orphan*/  activelow; int /*<<< orphan*/  index; } ;
struct b43_leds {TYPE_3__ led_radio; TYPE_2__ led_assoc; TYPE_1__ led_rx; TYPE_5__ led_tx; } ;
struct TYPE_9__ {struct b43_leds leds; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43_led_turn_off (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void b43_leds_exit(struct b43_wldev *dev)
{
	struct b43_leds *leds = &dev->wl->leds;

	b43_led_turn_off(dev, leds->led_tx.index, leds->led_tx.activelow);
	b43_led_turn_off(dev, leds->led_rx.index, leds->led_rx.activelow);
	b43_led_turn_off(dev, leds->led_assoc.index, leds->led_assoc.activelow);
	b43_led_turn_off(dev, leds->led_radio.index, leds->led_radio.activelow);
}