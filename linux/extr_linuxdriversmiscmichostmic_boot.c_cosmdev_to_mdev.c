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
struct mic_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct cosm_device {TYPE_1__ dev; } ;

/* Variables and functions */
 struct mic_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct mic_device *cosmdev_to_mdev(struct cosm_device *cdev)
{
	return dev_get_drvdata(cdev->dev.parent);
}