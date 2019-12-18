#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pointer; } ;
union acpi_object {TYPE_1__ buffer; } ;
typedef  void* u64 ;
struct spi_settings {void* reset_rec_usec; void* reset_a2r_usec; void* spi_cs_delay; } ;
struct applespi_data {TYPE_2__* spi; struct spi_settings spi_settings; } ;
struct acpi_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  acpi_dev_get_property (struct acpi_device*,char*,int /*<<< orphan*/ ,union acpi_object const**) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,void*,void*,void*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int applespi_get_spi_settings(struct applespi_data *applespi)
{
	struct acpi_device *adev = ACPI_COMPANION(&applespi->spi->dev);
	const union acpi_object *o;
	struct spi_settings *settings = &applespi->spi_settings;

	if (!acpi_dev_get_property(adev, "spiCSDelay", ACPI_TYPE_BUFFER, &o))
		settings->spi_cs_delay = *(u64 *)o->buffer.pointer;
	else
		dev_warn(&applespi->spi->dev,
			 "Property spiCSDelay not found\n");

	if (!acpi_dev_get_property(adev, "resetA2RUsec", ACPI_TYPE_BUFFER, &o))
		settings->reset_a2r_usec = *(u64 *)o->buffer.pointer;
	else
		dev_warn(&applespi->spi->dev,
			 "Property resetA2RUsec not found\n");

	if (!acpi_dev_get_property(adev, "resetRecUsec", ACPI_TYPE_BUFFER, &o))
		settings->reset_rec_usec = *(u64 *)o->buffer.pointer;
	else
		dev_warn(&applespi->spi->dev,
			 "Property resetRecUsec not found\n");

	dev_dbg(&applespi->spi->dev,
		"SPI settings: spi_cs_delay=%llu reset_a2r_usec=%llu reset_rec_usec=%llu\n",
		settings->spi_cs_delay, settings->reset_a2r_usec,
		settings->reset_rec_usec);

	return 0;
}