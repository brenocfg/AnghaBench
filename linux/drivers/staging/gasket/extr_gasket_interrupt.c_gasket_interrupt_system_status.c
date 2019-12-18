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
struct gasket_dev {int /*<<< orphan*/  dev; TYPE_1__* interrupt_data; } ;
struct TYPE_2__ {scalar_t__ num_configured; scalar_t__ num_interrupts; } ;

/* Variables and functions */
 int GASKET_STATUS_ALIVE ; 
 int GASKET_STATUS_DEAD ; 
 int GASKET_STATUS_LAMED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 

int gasket_interrupt_system_status(struct gasket_dev *gasket_dev)
{
	if (!gasket_dev->interrupt_data) {
		dev_dbg(gasket_dev->dev, "Interrupt data is null\n");
		return GASKET_STATUS_DEAD;
	}

	if (gasket_dev->interrupt_data->num_configured !=
		gasket_dev->interrupt_data->num_interrupts) {
		dev_dbg(gasket_dev->dev,
			"Not all interrupts were configured\n");
		return GASKET_STATUS_LAMED;
	}

	return GASKET_STATUS_ALIVE;
}