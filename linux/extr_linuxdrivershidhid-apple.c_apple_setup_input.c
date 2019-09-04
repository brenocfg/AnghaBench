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
struct input_dev {int /*<<< orphan*/  keybit; } ;
struct apple_key_translation {int /*<<< orphan*/  to; scalar_t__ from; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_NUMLOCK ; 
 struct apple_key_translation* apple_fn_keys ; 
 struct apple_key_translation* apple_iso_keyboard ; 
 struct apple_key_translation* powerbook_fn_keys ; 
 struct apple_key_translation* powerbook_numlock_keys ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apple_setup_input(struct input_dev *input)
{
	const struct apple_key_translation *trans;

	set_bit(KEY_NUMLOCK, input->keybit);

	/* Enable all needed keys */
	for (trans = apple_fn_keys; trans->from; trans++)
		set_bit(trans->to, input->keybit);

	for (trans = powerbook_fn_keys; trans->from; trans++)
		set_bit(trans->to, input->keybit);

	for (trans = powerbook_numlock_keys; trans->from; trans++)
		set_bit(trans->to, input->keybit);

	for (trans = apple_iso_keyboard; trans->from; trans++)
		set_bit(trans->to, input->keybit);
}