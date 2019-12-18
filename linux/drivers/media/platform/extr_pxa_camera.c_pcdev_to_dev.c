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
struct TYPE_2__ {struct device* dev; } ;
struct pxa_camera_dev {TYPE_1__ v4l2_dev; } ;
struct device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct device *pcdev_to_dev(struct pxa_camera_dev *pcdev)
{
	return pcdev->v4l2_dev.dev;
}