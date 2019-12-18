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
struct adp5589_kpad {unsigned short* keycode; TYPE_2__* client; TYPE_1__* var; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int keymapsize; } ;

/* Variables and functions */
 int EINVAL ; 
 int KEY_EV_PRESSED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int adp5589_get_evcode(struct adp5589_kpad *kpad, unsigned short key)
{
	int i;

	for (i = 0; i < kpad->var->keymapsize; i++)
		if (key == kpad->keycode[i])
			return (i + 1) | KEY_EV_PRESSED;

	dev_err(&kpad->client->dev, "RESET/UNLOCK key not in keycode map\n");

	return -EINVAL;
}