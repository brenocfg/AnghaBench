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
typedef  unsigned int u16 ;
struct input_dev {unsigned int* keycode; } ;
struct firedtv {int /*<<< orphan*/  device; struct input_dev* remote_ctrl_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,unsigned int,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 unsigned int* oldtable ; 

void fdtv_handle_rc(struct firedtv *fdtv, unsigned int code)
{
	struct input_dev *idev = fdtv->remote_ctrl_dev;
	u16 *keycode = idev->keycode;

	if (code >= 0x0300 && code <= 0x031f)
		code = keycode[code - 0x0300];
	else if (code >= 0x0340 && code <= 0x0354)
		code = keycode[code - 0x0320];
	else if (code >= 0x4501 && code <= 0x451f)
		code = oldtable[code - 0x4501];
	else if (code >= 0x4540 && code <= 0x4542)
		code = oldtable[code - 0x4521];
	else {
		dev_dbg(fdtv->device,
			"invalid key code 0x%04x from remote control\n",
			code);
		return;
	}

	input_report_key(idev, code, 1);
	input_sync(idev);
	input_report_key(idev, code, 0);
	input_sync(idev);
}