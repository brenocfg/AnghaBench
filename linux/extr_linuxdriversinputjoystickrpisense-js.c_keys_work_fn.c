#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct rpisense_js {int /*<<< orphan*/  keys_dev; } ;
typedef  int s32 ;
struct TYPE_3__ {struct rpisense_js joystick; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPISENSE_KEYS ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * keymap ; 
 TYPE_1__* rpisense ; 
 int rpisense_reg_read (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void keys_work_fn(struct work_struct *work)
{
	int i;
	static s32 prev_keys;
	struct rpisense_js *rpisense_js = &rpisense->joystick;
	s32 keys = rpisense_reg_read(rpisense, RPISENSE_KEYS);
	s32 changes = keys ^ prev_keys;

	prev_keys = keys;
	for (i = 0; i < 5; i++) {
		if (changes & 1) {
			input_report_key(rpisense_js->keys_dev,
					 keymap[i], keys & 1);
		}
		changes >>= 1;
		keys >>= 1;
	}
	input_sync(rpisense_js->keys_dev);
}