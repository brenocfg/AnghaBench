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
struct hsi_controller {unsigned int num_ports; int /*<<< orphan*/  device; TYPE_1__** port; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

void hsi_put_controller(struct hsi_controller *hsi)
{
	unsigned int i;

	if (!hsi)
		return;

	for (i = 0; i < hsi->num_ports; i++)
		if (hsi->port && hsi->port[i])
			put_device(&hsi->port[i]->device);
	put_device(&hsi->device);
}