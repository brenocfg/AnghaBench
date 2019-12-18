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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENODEV ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,char*) ; 
 int /*<<< orphan*/  spk_strlwr (char*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 TYPE_1__* synth ; 
 scalar_t__ synth_init (char*) ; 

__attribute__((used)) static ssize_t synth_store(struct kobject *kobj, struct kobj_attribute *attr,
			   const char *buf, size_t count)
{
	int len;
	char new_synth_name[10];

	len = strlen(buf);
	if (len < 2 || len > 9)
		return -EINVAL;
	memcpy(new_synth_name, buf, len);
	if (new_synth_name[len - 1] == '\n')
		len--;
	new_synth_name[len] = '\0';
	spk_strlwr(new_synth_name);
	if (synth && !strcmp(new_synth_name, synth->name)) {
		pr_warn("%s already in use\n", new_synth_name);
	} else if (synth_init(new_synth_name) != 0) {
		pr_warn("failed to init synth %s\n", new_synth_name);
		return -ENODEV;
	}
	return count;
}