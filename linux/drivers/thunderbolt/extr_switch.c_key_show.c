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
struct tb_switch {TYPE_1__* tb; scalar_t__ key; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_SWITCH_KEY_SIZE ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restart_syscall () ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 struct tb_switch* tb_to_switch (struct device*) ; 

__attribute__((used)) static ssize_t key_show(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	struct tb_switch *sw = tb_to_switch(dev);
	ssize_t ret;

	if (!mutex_trylock(&sw->tb->lock))
		return restart_syscall();

	if (sw->key)
		ret = sprintf(buf, "%*phN\n", TB_SWITCH_KEY_SIZE, sw->key);
	else
		ret = sprintf(buf, "\n");

	mutex_unlock(&sw->tb->lock);
	return ret;
}