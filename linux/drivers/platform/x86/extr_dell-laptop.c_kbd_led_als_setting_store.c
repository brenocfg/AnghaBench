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
typedef  int /*<<< orphan*/  u8 ;
struct kbd_state {int /*<<< orphan*/  als_setting; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int kbd_get_state (struct kbd_state*) ; 
 int /*<<< orphan*/  kbd_led_mutex ; 
 int kbd_set_state_safe (struct kbd_state*,struct kbd_state*) ; 
 int kstrtou8 (char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t kbd_led_als_setting_store(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf, size_t count)
{
	struct kbd_state state;
	struct kbd_state new_state;
	u8 setting;
	int ret;

	ret = kstrtou8(buf, 10, &setting);
	if (ret)
		return ret;

	mutex_lock(&kbd_led_mutex);

	ret = kbd_get_state(&state);
	if (ret)
		goto out;

	new_state = state;
	new_state.als_setting = setting;

	ret = kbd_set_state_safe(&new_state, &state);
	if (ret)
		goto out;

	ret = count;
out:
	mutex_unlock(&kbd_led_mutex);
	return ret;
}