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
struct input_dev {int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 scalar_t__ EV_KEY ; 
 scalar_t__ KEY_MAX ; 
 scalar_t__* cmpc_keys_codes ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmpc_keys_idev_init(struct input_dev *inputdev)
{
	int i;

	set_bit(EV_KEY, inputdev->evbit);
	for (i = 0; cmpc_keys_codes[i] != KEY_MAX; i++)
		set_bit(cmpc_keys_codes[i], inputdev->keybit);
}