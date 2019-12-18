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
struct keyboard_protocol {unsigned char fn_pressed; int modifiers; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int BIT (int) ; 
 int /*<<< orphan*/ * applespi_controlcodes ; 
 int fnremap ; 

__attribute__((used)) static void
applespi_remap_fn_key(struct keyboard_protocol *keyboard_protocol)
{
	unsigned char tmp;
	u8 bit = BIT((fnremap - 1) & 0x07);

	if (!fnremap || fnremap > ARRAY_SIZE(applespi_controlcodes) ||
	    !applespi_controlcodes[fnremap - 1])
		return;

	tmp = keyboard_protocol->fn_pressed;
	keyboard_protocol->fn_pressed = !!(keyboard_protocol->modifiers & bit);
	if (tmp)
		keyboard_protocol->modifiers |= bit;
	else
		keyboard_protocol->modifiers &= ~bit;
}