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
struct TYPE_2__ {int* data; scalar_t__ curdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 TYPE_1__ hil_dev ; 
 int* hphilkeyb_keycode ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void poll_finished(void)
{
	int down;
	int key;
	unsigned char scode;

	switch (hil_dev.data[0]) {
	case 0x40:
		down = (hil_dev.data[1] & 1) == 0;
		scode = hil_dev.data[1] >> 1;
		key = hphilkeyb_keycode[scode];
		input_report_key(hil_dev.dev, key, down);
		break;
	}
	hil_dev.curdev = 0;
}