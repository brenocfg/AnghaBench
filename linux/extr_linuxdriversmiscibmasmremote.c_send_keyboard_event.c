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
struct TYPE_3__ {unsigned short key_code; int /*<<< orphan*/  key_down; } ;
struct TYPE_4__ {TYPE_1__ keyboard; } ;
struct remote_input {TYPE_2__ data; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_report_key (struct input_dev*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 unsigned int* xlate ; 
 unsigned int* xlate_high ; 

__attribute__((used)) static void send_keyboard_event(struct input_dev *dev,
		struct remote_input *input)
{
	unsigned int key;
	unsigned short code = input->data.keyboard.key_code;

	if (code & 0xff00)
		key = xlate_high[code & 0xff];
	else
		key = xlate[code];
	input_report_key(dev, key, input->data.keyboard.key_down);
	input_sync(dev);
}