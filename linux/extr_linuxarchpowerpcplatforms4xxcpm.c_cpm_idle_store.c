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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  cpm_idle_config (int) ; 
 TYPE_1__* idle_mode ; 
 char* memchr (char const*,char,size_t) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t cpm_idle_store(struct kobject *kobj,
			      struct kobj_attribute *attr,
			      const char *buf, size_t n)
{
	int i;
	char *p;
	int len;

	p = memchr(buf, '\n', n);
	len = p ? p - buf : n;

	for (i = 0; i < ARRAY_SIZE(idle_mode); i++) {
		if (strncmp(buf, idle_mode[i].name, len) == 0) {
			cpm_idle_config(i);
			return n;
		}
	}

	return -EINVAL;
}