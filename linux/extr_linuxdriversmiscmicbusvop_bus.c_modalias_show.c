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
struct TYPE_2__ {int device; int vendor; } ;
struct vop_device {TYPE_1__ id; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct vop_device* dev_to_vop (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

__attribute__((used)) static ssize_t modalias_show(struct device *d,
			     struct device_attribute *attr, char *buf)
{
	struct vop_device *dev = dev_to_vop(d);

	return sprintf(buf, "vop:d%08Xv%08X\n",
		       dev->id.device, dev->id.vendor);
}