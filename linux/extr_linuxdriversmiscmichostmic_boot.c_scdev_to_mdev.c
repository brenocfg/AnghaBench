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
struct scif_hw_dev {TYPE_1__ dev; } ;
struct mic_device {int dummy; } ;

/* Variables and functions */
 struct mic_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct mic_device *scdev_to_mdev(struct scif_hw_dev *scdev)
{
	return dev_get_drvdata(scdev->dev.parent);
}