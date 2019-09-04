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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct vop_device {TYPE_1__ dev; } ;
struct mic_driver {int dummy; } ;

/* Variables and functions */
 struct mic_driver* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct mic_driver *vpdev_to_mdrv(struct vop_device *vpdev)
{
	return dev_get_drvdata(vpdev->dev.parent);
}