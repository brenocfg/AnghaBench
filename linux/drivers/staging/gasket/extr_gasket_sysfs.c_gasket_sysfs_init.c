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
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * device; } ;

/* Variables and functions */
 int GASKET_SYSFS_NUM_MAPPINGS ; 
 TYPE_1__* dev_mappings ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void gasket_sysfs_init(void)
{
	int i;

	for (i = 0; i < GASKET_SYSFS_NUM_MAPPINGS; i++) {
		dev_mappings[i].device = NULL;
		mutex_init(&dev_mappings[i].mutex);
	}
}