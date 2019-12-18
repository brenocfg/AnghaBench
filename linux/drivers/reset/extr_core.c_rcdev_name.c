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
struct reset_controller_dev {TYPE_1__* of_node; scalar_t__ dev; } ;
struct TYPE_2__ {char const* full_name; } ;

/* Variables and functions */
 char const* dev_name (scalar_t__) ; 

__attribute__((used)) static const char *rcdev_name(struct reset_controller_dev *rcdev)
{
	if (rcdev->dev)
		return dev_name(rcdev->dev);

	if (rcdev->of_node)
		return rcdev->of_node->full_name;

	return NULL;
}