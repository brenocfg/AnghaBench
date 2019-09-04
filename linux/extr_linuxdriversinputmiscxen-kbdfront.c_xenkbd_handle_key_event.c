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
struct xenkbd_key {int pressed; int /*<<< orphan*/  keycode; } ;
struct xenkbd_info {struct input_dev* kbd; struct input_dev* ptr; } ;
struct input_dev {int /*<<< orphan*/  key; int /*<<< orphan*/  keybit; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void xenkbd_handle_key_event(struct xenkbd_info *info,
				    struct xenkbd_key *key)
{
	struct input_dev *dev;
	int value = key->pressed;

	if (test_bit(key->keycode, info->ptr->keybit)) {
		dev = info->ptr;
	} else if (test_bit(key->keycode, info->kbd->keybit)) {
		dev = info->kbd;
		if (key->pressed && test_bit(key->keycode, info->kbd->key))
			value = 2; /* Mark as autorepeat */
	} else {
		pr_warn("unhandled keycode 0x%x\n", key->keycode);
		return;
	}

	if (unlikely(!dev))
		return;

	input_event(dev, EV_KEY, key->keycode, value);
	input_sync(dev);
}