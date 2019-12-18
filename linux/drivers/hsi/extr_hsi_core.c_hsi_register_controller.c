#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* parent; } ;
struct hsi_controller {unsigned int num_ports; TYPE_2__ device; TYPE_1__** port; } ;
struct TYPE_4__ {TYPE_2__ device; } ;

/* Variables and functions */
 int device_add (TYPE_2__*) ; 
 int /*<<< orphan*/  device_del (TYPE_2__*) ; 
 int /*<<< orphan*/  hsi_scan_board_info (struct hsi_controller*) ; 

int hsi_register_controller(struct hsi_controller *hsi)
{
	unsigned int i;
	int err;

	err = device_add(&hsi->device);
	if (err < 0)
		return err;
	for (i = 0; i < hsi->num_ports; i++) {
		hsi->port[i]->device.parent = &hsi->device;
		err = device_add(&hsi->port[i]->device);
		if (err < 0)
			goto out;
	}
	/* Populate HSI bus with HSI clients */
	hsi_scan_board_info(hsi);

	return 0;
out:
	while (i-- > 0)
		device_del(&hsi->port[i]->device);
	device_del(&hsi->device);

	return err;
}