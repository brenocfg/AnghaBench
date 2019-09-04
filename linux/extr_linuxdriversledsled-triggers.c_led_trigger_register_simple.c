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
struct led_trigger {char const* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct led_trigger*) ; 
 struct led_trigger* kzalloc (int,int /*<<< orphan*/ ) ; 
 int led_trigger_register (struct led_trigger*) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*,...) ; 

void led_trigger_register_simple(const char *name, struct led_trigger **tp)
{
	struct led_trigger *trig;
	int err;

	trig = kzalloc(sizeof(struct led_trigger), GFP_KERNEL);

	if (trig) {
		trig->name = name;
		err = led_trigger_register(trig);
		if (err < 0) {
			kfree(trig);
			trig = NULL;
			pr_warn("LED trigger %s failed to register (%d)\n",
				name, err);
		}
	} else {
		pr_warn("LED trigger %s failed to register (no memory)\n",
			name);
	}
	*tp = trig;
}