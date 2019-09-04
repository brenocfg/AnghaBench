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
struct radio_isa_driver {int num_of_io_ports; int* io_ports; } ;

/* Variables and functions */

__attribute__((used)) static bool radio_isa_valid_io(const struct radio_isa_driver *drv, int io)
{
	int i;

	for (i = 0; i < drv->num_of_io_ports; i++)
		if (drv->io_ports[i] == io)
			return true;
	return false;
}