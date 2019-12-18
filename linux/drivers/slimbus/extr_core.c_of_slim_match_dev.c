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
struct TYPE_2__ {struct device_node* of_node; } ;
struct slim_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct slim_device* to_slim_device (struct device*) ; 

__attribute__((used)) static int of_slim_match_dev(struct device *dev, void *data)
{
	struct device_node *np = data;
	struct slim_device *sbdev = to_slim_device(dev);

	return (sbdev->dev.of_node == np);
}