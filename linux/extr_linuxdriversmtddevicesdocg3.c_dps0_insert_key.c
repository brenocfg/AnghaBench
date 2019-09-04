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
struct docg3 {TYPE_1__* cascade; int /*<<< orphan*/  device_id; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOC_DPS0_KEY ; 
 size_t DOC_LAYOUT_DPS_KEY_LENGTH ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  doc_set_device_id (struct docg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doc_writeb (struct docg3*,char const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct docg3* sysfs_dev2docg3 (struct device*,struct device_attribute*) ; 

__attribute__((used)) static ssize_t dps0_insert_key(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	struct docg3 *docg3 = sysfs_dev2docg3(dev, attr);
	int i;

	if (count != DOC_LAYOUT_DPS_KEY_LENGTH)
		return -EINVAL;

	mutex_lock(&docg3->cascade->lock);
	doc_set_device_id(docg3, docg3->device_id);
	for (i = 0; i < DOC_LAYOUT_DPS_KEY_LENGTH; i++)
		doc_writeb(docg3, buf[i], DOC_DPS0_KEY);
	doc_set_device_id(docg3, 0);
	mutex_unlock(&docg3->cascade->lock);
	return count;
}