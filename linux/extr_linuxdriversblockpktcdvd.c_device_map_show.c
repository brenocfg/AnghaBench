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
struct pktcdvd_device {char* name; TYPE_1__* bdev; int /*<<< orphan*/  pkt_dev; } ;
struct class_attribute {int dummy; } ;
struct class {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int MAJOR (int /*<<< orphan*/ ) ; 
 int MAX_WRITERS ; 
 int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  ctl_mutex ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct pktcdvd_device** pkt_devs ; 
 scalar_t__ sprintf (char*,char*,char*,int,int,int,int) ; 

__attribute__((used)) static ssize_t device_map_show(struct class *c, struct class_attribute *attr,
			       char *data)
{
	int n = 0;
	int idx;
	mutex_lock_nested(&ctl_mutex, SINGLE_DEPTH_NESTING);
	for (idx = 0; idx < MAX_WRITERS; idx++) {
		struct pktcdvd_device *pd = pkt_devs[idx];
		if (!pd)
			continue;
		n += sprintf(data+n, "%s %u:%u %u:%u\n",
			pd->name,
			MAJOR(pd->pkt_dev), MINOR(pd->pkt_dev),
			MAJOR(pd->bdev->bd_dev),
			MINOR(pd->bdev->bd_dev));
	}
	mutex_unlock(&ctl_mutex);
	return n;
}