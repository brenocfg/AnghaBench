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
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct scif_hw_dev {TYPE_1__ dev; } ;
struct scif_driver {int /*<<< orphan*/  (* remove ) (struct scif_hw_dev*) ;} ;
struct device {int dummy; } ;

/* Variables and functions */
 struct scif_hw_dev* dev_to_scif (struct device*) ; 
 struct scif_driver* drv_to_scif (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scif_hw_dev*) ; 

__attribute__((used)) static int scif_dev_remove(struct device *d)
{
	struct scif_hw_dev *dev = dev_to_scif(d);
	struct scif_driver *drv = drv_to_scif(dev->dev.driver);

	drv->remove(dev);
	return 0;
}