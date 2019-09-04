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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DEVICE_MINOR ; 
 int ENXIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int iminor (struct inode*) ; 
 TYPE_1__* inst ; 

__attribute__((used)) static int bcm2835_gpiomem_open(struct inode *inode, struct file *file)
{
	int dev = iminor(inode);
	int ret = 0;

	if (dev != DEVICE_MINOR) {
		dev_err(inst->dev, "Unknown minor device: %d", dev);
		ret = -ENXIO;
	}
	return ret;
}