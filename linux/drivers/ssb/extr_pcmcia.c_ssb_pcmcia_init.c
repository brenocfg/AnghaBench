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
struct ssb_bus {scalar_t__ bustype; TYPE_1__* host_pcmcia; int /*<<< orphan*/  sprom_mutex; int /*<<< orphan*/  sprom_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SSB_BUSTYPE_PCMCIA ; 
 int /*<<< orphan*/  SSB_PCMCIA_SPROM_SIZE ; 
 int /*<<< orphan*/  dev_attr_ssb_sprom ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int ssb_pcmcia_hardware_setup (struct ssb_bus*) ; 

int ssb_pcmcia_init(struct ssb_bus *bus)
{
	int err;

	if (bus->bustype != SSB_BUSTYPE_PCMCIA)
		return 0;

	err = ssb_pcmcia_hardware_setup(bus);
	if (err)
		goto error;

	bus->sprom_size = SSB_PCMCIA_SPROM_SIZE;
	mutex_init(&bus->sprom_mutex);
	err = device_create_file(&bus->host_pcmcia->dev, &dev_attr_ssb_sprom);
	if (err)
		goto error;

	return 0;
error:
	pr_err("Failed to initialize PCMCIA host device\n");
	return err;
}