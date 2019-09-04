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

/* Variables and functions */
 unsigned char KEYB_KEYREG ; 
 int /*<<< orphan*/ * adbhid ; 
 int /*<<< orphan*/  adbhid_input_keycode (int,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,unsigned char,unsigned char,unsigned char,unsigned char) ; 

__attribute__((used)) static void
adbhid_keyboard_input(unsigned char *data, int nb, int apoll)
{
	int id = (data[0] >> 4) & 0x0f;

	if (!adbhid[id]) {
		pr_err("ADB HID on ID %d not yet registered, packet %#02x, %#02x, %#02x, %#02x\n",
		       id, data[0], data[1], data[2], data[3]);
		return;
	}

	/* first check this is from register 0 */
	if (nb != 3 || (data[0] & 3) != KEYB_KEYREG)
		return;		/* ignore it */
	adbhid_input_keycode(id, data[1], 0);
	if (!(data[2] == 0xff || (data[2] == 0x7f && data[1] == 0x7f)))
		adbhid_input_keycode(id, data[2], 0);
}