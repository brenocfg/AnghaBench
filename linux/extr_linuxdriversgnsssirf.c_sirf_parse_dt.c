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
typedef  int u32 ;
struct sirf_data {int speed; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct serdev_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 struct sirf_data* serdev_device_get_drvdata (struct serdev_device*) ; 

__attribute__((used)) static int sirf_parse_dt(struct serdev_device *serdev)
{
	struct sirf_data *data = serdev_device_get_drvdata(serdev);
	struct device_node *node = serdev->dev.of_node;
	u32 speed = 9600;

	of_property_read_u32(node, "current-speed", &speed);

	data->speed = speed;

	return 0;
}