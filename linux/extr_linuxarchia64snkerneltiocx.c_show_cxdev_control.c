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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int nasid; int part_num; int mfg_num; } ;
struct cx_dev {int bt; TYPE_1__ cx_id; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int) ; 
 struct cx_dev* to_cx_dev (struct device*) ; 

__attribute__((used)) static ssize_t show_cxdev_control(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct cx_dev *cx_dev = to_cx_dev(dev);

	return sprintf(buf, "0x%x 0x%x 0x%x 0x%x\n",
		       cx_dev->cx_id.nasid,
		       cx_dev->cx_id.part_num, cx_dev->cx_id.mfg_num,
		       cx_dev->bt);
}