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
struct TYPE_3__ {int /*<<< orphan*/  release_str; int /*<<< orphan*/  repeat_str; int /*<<< orphan*/  press_str; } ;
struct TYPE_4__ {TYPE_1__ kbd; } ;
struct logical_input {int rise_time; int fall_time; int /*<<< orphan*/  list; TYPE_2__ u; int /*<<< orphan*/  state; int /*<<< orphan*/  type; int /*<<< orphan*/  value; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INPUT_ST_LOW ; 
 int /*<<< orphan*/  INPUT_TYPE_KBD ; 
 int /*<<< orphan*/  input_name2mask (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct logical_input*) ; 
 struct logical_input* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logical_inputs ; 
 int /*<<< orphan*/  scan_mask_i ; 
 int /*<<< orphan*/  scan_mask_o ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static struct logical_input *panel_bind_key(const char *name, const char *press,
					    const char *repeat,
					    const char *release)
{
	struct logical_input *key;

	key = kzalloc(sizeof(*key), GFP_KERNEL);
	if (!key)
		return NULL;

	if (!input_name2mask(name, &key->mask, &key->value, &scan_mask_i,
			     &scan_mask_o)) {
		kfree(key);
		return NULL;
	}

	key->type = INPUT_TYPE_KBD;
	key->state = INPUT_ST_LOW;
	key->rise_time = 1;
	key->fall_time = 1;

	strncpy(key->u.kbd.press_str, press, sizeof(key->u.kbd.press_str));
	strncpy(key->u.kbd.repeat_str, repeat, sizeof(key->u.kbd.repeat_str));
	strncpy(key->u.kbd.release_str, release,
		sizeof(key->u.kbd.release_str));
	list_add(&key->list, &logical_inputs);
	return key;
}