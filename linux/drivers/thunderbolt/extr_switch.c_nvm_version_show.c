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
struct tb_switch {TYPE_2__* tb; TYPE_1__* nvm; scalar_t__ safe_mode; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int major; int minor; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODATA ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int restart_syscall () ; 
 int sprintf (char*,char*,int,int) ; 
 struct tb_switch* tb_to_switch (struct device*) ; 

__attribute__((used)) static ssize_t nvm_version_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct tb_switch *sw = tb_to_switch(dev);
	int ret;

	if (!mutex_trylock(&sw->tb->lock))
		return restart_syscall();

	if (sw->safe_mode)
		ret = -ENODATA;
	else if (!sw->nvm)
		ret = -EAGAIN;
	else
		ret = sprintf(buf, "%x.%x\n", sw->nvm->major, sw->nvm->minor);

	mutex_unlock(&sw->tb->lock);

	return ret;
}