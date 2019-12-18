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
typedef  int /*<<< orphan*/  u8 ;
struct tb_switch {TYPE_1__* tb; int /*<<< orphan*/ * key; scalar_t__ authorized; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 size_t EBUSY ; 
 size_t EINVAL ; 
 size_t ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TB_SWITCH_KEY_SIZE ; 
 scalar_t__ hex2bin (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t restart_syscall () ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 struct tb_switch* tb_to_switch (struct device*) ; 

__attribute__((used)) static ssize_t key_store(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct tb_switch *sw = tb_to_switch(dev);
	u8 key[TB_SWITCH_KEY_SIZE];
	ssize_t ret = count;
	bool clear = false;

	if (!strcmp(buf, "\n"))
		clear = true;
	else if (hex2bin(key, buf, sizeof(key)))
		return -EINVAL;

	if (!mutex_trylock(&sw->tb->lock))
		return restart_syscall();

	if (sw->authorized) {
		ret = -EBUSY;
	} else {
		kfree(sw->key);
		if (clear) {
			sw->key = NULL;
		} else {
			sw->key = kmemdup(key, sizeof(key), GFP_KERNEL);
			if (!sw->key)
				ret = -ENOMEM;
		}
	}

	mutex_unlock(&sw->tb->lock);
	return ret;
}