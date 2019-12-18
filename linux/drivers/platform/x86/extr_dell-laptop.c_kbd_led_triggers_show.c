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
struct kbd_state {int triggers; int /*<<< orphan*/  mode_bit; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int triggers; } ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int BIT (int) ; 
 int kbd_get_level (struct kbd_state*) ; 
 int kbd_get_state (struct kbd_state*) ; 
 TYPE_1__ kbd_info ; 
 int kbd_is_trigger_mode_bit (int /*<<< orphan*/ ) ; 
 char** kbd_led_triggers ; 
 scalar_t__ kbd_triggers_supported ; 
 scalar_t__ sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t kbd_led_triggers_show(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct kbd_state state;
	bool triggers_enabled;
	int level, i, ret;
	int len = 0;

	ret = kbd_get_state(&state);
	if (ret)
		return ret;

	len = 0;

	if (kbd_triggers_supported) {
		triggers_enabled = kbd_is_trigger_mode_bit(state.mode_bit);
		level = kbd_get_level(&state);
		for (i = 0; i < ARRAY_SIZE(kbd_led_triggers); ++i) {
			if (!(kbd_info.triggers & BIT(i)))
				continue;
			if (!kbd_led_triggers[i])
				continue;
			if ((triggers_enabled || level <= 0) &&
			    (state.triggers & BIT(i)))
				buf[len++] = '+';
			else
				buf[len++] = '-';
			len += sprintf(buf+len, "%s ", kbd_led_triggers[i]);
		}
	}

	if (len)
		buf[len - 1] = '\n';

	return len;
}