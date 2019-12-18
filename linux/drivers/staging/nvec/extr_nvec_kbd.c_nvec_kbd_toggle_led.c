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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int caps_lock; int /*<<< orphan*/  nvec; } ;

/* Variables and functions */
 char BIT (int) ; 
 char NVEC_KBD ; 
 char SET_LEDS ; 
 TYPE_1__ keys_dev ; 
 int /*<<< orphan*/  nvec_write_async (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void nvec_kbd_toggle_led(void)
{
	char buf[] = { NVEC_KBD, SET_LEDS, 0 };

	keys_dev.caps_lock = !keys_dev.caps_lock;

	if (keys_dev.caps_lock)
		/* should be BIT(0) only, firmware bug? */
		buf[2] = BIT(0) | BIT(1) | BIT(2);

	nvec_write_async(keys_dev.nvec, buf, sizeof(buf));
}