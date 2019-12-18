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
struct TYPE_2__ {int /*<<< orphan*/  (* show_label ) (struct device*,struct device_attribute*,char*) ;} ;
struct abx500_temp {TYPE_1__ ops; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct abx500_temp* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct device*,struct device_attribute*,char*) ; 

__attribute__((used)) static ssize_t label_show(struct device *dev,
			  struct device_attribute *devattr, char *buf)
{
	struct abx500_temp *data = dev_get_drvdata(dev);
	/* Show each sensor label */
	return data->ops.show_label(dev, devattr, buf);
}