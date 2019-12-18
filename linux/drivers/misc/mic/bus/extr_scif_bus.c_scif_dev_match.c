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
struct scif_hw_dev_id {scalar_t__ device; } ;
struct scif_hw_dev {int dummy; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct scif_hw_dev_id* id_table; } ;

/* Variables and functions */
 struct scif_hw_dev* dev_to_scif (struct device*) ; 
 TYPE_1__* drv_to_scif (struct device_driver*) ; 
 scalar_t__ scif_id_match (struct scif_hw_dev*,struct scif_hw_dev_id const*) ; 

__attribute__((used)) static int scif_dev_match(struct device *dv, struct device_driver *dr)
{
	unsigned int i;
	struct scif_hw_dev *dev = dev_to_scif(dv);
	const struct scif_hw_dev_id *ids;

	ids = drv_to_scif(dr)->id_table;
	for (i = 0; ids[i].device; i++)
		if (scif_id_match(dev, &ids[i]))
			return 1;
	return 0;
}