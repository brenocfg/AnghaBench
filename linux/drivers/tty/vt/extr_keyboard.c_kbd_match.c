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
struct input_handler {int dummy; } ;
struct input_dev {int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 int BTN_MISC ; 
 int EV_KEY ; 
 int EV_SND ; 
 int KEY_BRL_DOT1 ; 
 int KEY_BRL_DOT10 ; 
 int KEY_RESERVED ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool kbd_match(struct input_handler *handler, struct input_dev *dev)
{
	int i;

	if (test_bit(EV_SND, dev->evbit))
		return true;

	if (test_bit(EV_KEY, dev->evbit)) {
		for (i = KEY_RESERVED; i < BTN_MISC; i++)
			if (test_bit(i, dev->keybit))
				return true;
		for (i = KEY_BRL_DOT1; i <= KEY_BRL_DOT10; i++)
			if (test_bit(i, dev->keybit))
				return true;
	}

	return false;
}