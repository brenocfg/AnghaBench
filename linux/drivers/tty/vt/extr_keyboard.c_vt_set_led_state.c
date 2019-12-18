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
struct kbd_struct {int dummy; } ;

/* Variables and functions */
 struct kbd_struct* kbd_table ; 
 int /*<<< orphan*/  setledstate (struct kbd_struct*,int) ; 

void vt_set_led_state(int console, int leds)
{
	struct kbd_struct *kb = kbd_table + console;
	setledstate(kb, leds);
}