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
struct nes_vnic {scalar_t__ of_device_registered; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct nes_ib_device {TYPE_1__ ibdev; struct nes_vnic* nesvnic; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_unregister_device (TYPE_1__*) ; 
 int /*<<< orphan*/ * nes_dev_attributes ; 

__attribute__((used)) static void nes_unregister_ofa_device(struct nes_ib_device *nesibdev)
{
	struct nes_vnic *nesvnic = nesibdev->nesvnic;
	int i;

	for (i = 0; i < ARRAY_SIZE(nes_dev_attributes); ++i) {
		device_remove_file(&nesibdev->ibdev.dev, nes_dev_attributes[i]);
	}

	if (nesvnic->of_device_registered) {
		ib_unregister_device(&nesibdev->ibdev);
	}

	nesvnic->of_device_registered = 0;
}