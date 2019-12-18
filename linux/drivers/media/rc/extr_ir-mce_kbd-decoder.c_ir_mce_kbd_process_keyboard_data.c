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
typedef  int u32 ;
struct rc_dev {int /*<<< orphan*/  input_dev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MCIR2_MASK_KEYS_START ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,unsigned char,int) ; 
 unsigned char* kbd_keycodes ; 

__attribute__((used)) static void ir_mce_kbd_process_keyboard_data(struct rc_dev *dev, u32 scancode)
{
	u8 keydata1  = (scancode >> 8) & 0xff;
	u8 keydata2  = (scancode >> 16) & 0xff;
	u8 shiftmask = scancode & 0xff;
	unsigned char maskcode;
	int i, keystate;

	dev_dbg(&dev->dev, "keyboard: keydata2 = 0x%02x, keydata1 = 0x%02x, shiftmask = 0x%02x\n",
		keydata2, keydata1, shiftmask);

	for (i = 0; i < 7; i++) {
		maskcode = kbd_keycodes[MCIR2_MASK_KEYS_START + i];
		if (shiftmask & (1 << i))
			keystate = 1;
		else
			keystate = 0;
		input_report_key(dev->input_dev, maskcode, keystate);
	}

	if (keydata1)
		input_report_key(dev->input_dev, kbd_keycodes[keydata1], 1);
	if (keydata2)
		input_report_key(dev->input_dev, kbd_keycodes[keydata2], 1);

	if (!keydata1 && !keydata2) {
		for (i = 0; i < MCIR2_MASK_KEYS_START; i++)
			input_report_key(dev->input_dev, kbd_keycodes[i], 0);
	}
}