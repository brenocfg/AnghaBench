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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct hidma_dev {int /*<<< orphan*/  chid_attrs; TYPE_1__ ddev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hidma_create_sysfs_entry (struct hidma_dev*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hidma_sysfs_init(struct hidma_dev *dev)
{
	dev->chid_attrs = hidma_create_sysfs_entry(dev, "chid", S_IRUGO);
	if (!dev->chid_attrs)
		return -ENOMEM;

	return device_create_file(dev->ddev.dev, dev->chid_attrs);
}