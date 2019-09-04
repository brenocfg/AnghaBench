#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ib_device {int /*<<< orphan*/  dev; } ;
struct rxe_dev {struct ib_device ib_dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_unregister_device (struct ib_device*) ; 
 int /*<<< orphan*/ * rxe_dev_attributes ; 

int rxe_unregister_device(struct rxe_dev *rxe)
{
	int i;
	struct ib_device *dev = &rxe->ib_dev;

	for (i = 0; i < ARRAY_SIZE(rxe_dev_attributes); ++i)
		device_remove_file(&dev->dev, rxe_dev_attributes[i]);

	ib_unregister_device(dev);

	return 0;
}