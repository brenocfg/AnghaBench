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
struct TYPE_2__ {int flags; } ;
struct pdcspath_entry {int /*<<< orphan*/  rw_lock; TYPE_1__ devpath; } ;
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct pdcspath_entry pdcspath_entry_primary ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t pdcs_auto_read(struct kobject *kobj,
			      struct kobj_attribute *attr,
			      char *buf, int knob)
{
	char *out = buf;
	struct pdcspath_entry *pathentry;

	if (!buf)
		return -EINVAL;

	/* Current flags are stored in primary boot path entry */
	pathentry = &pdcspath_entry_primary;

	read_lock(&pathentry->rw_lock);
	out += sprintf(out, "%s\n", (pathentry->devpath.flags & knob) ?
					"On" : "Off");
	read_unlock(&pathentry->rw_lock);

	return out - buf;
}