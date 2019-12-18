#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS1390_REG_TRICKLE ; 
 int /*<<< orphan*/  DS1390_TRICKLE_CHARGER_250_OHM ; 
 int /*<<< orphan*/  DS1390_TRICKLE_CHARGER_2K_OHM ; 
 int /*<<< orphan*/  DS1390_TRICKLE_CHARGER_4K_OHM ; 
 int /*<<< orphan*/  DS1390_TRICKLE_CHARGER_DIODE ; 
 int /*<<< orphan*/  DS1390_TRICKLE_CHARGER_ENABLE ; 
 int /*<<< orphan*/  DS1390_TRICKLE_CHARGER_NO_DIODE ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  ds1390_set_reg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static void ds1390_trickle_of_init(struct spi_device *spi)
{
	u32 ohms = 0;
	u8 value;

	if (of_property_read_u32(spi->dev.of_node, "trickle-resistor-ohms",
				 &ohms))
		goto out;

	/* Enable charger */
	value = DS1390_TRICKLE_CHARGER_ENABLE;
	if (of_property_read_bool(spi->dev.of_node, "trickle-diode-disable"))
		value |= DS1390_TRICKLE_CHARGER_NO_DIODE;
	else
		value |= DS1390_TRICKLE_CHARGER_DIODE;

	/* Resistor select */
	switch (ohms) {
	case 250:
		value |= DS1390_TRICKLE_CHARGER_250_OHM;
		break;
	case 2000:
		value |= DS1390_TRICKLE_CHARGER_2K_OHM;
		break;
	case 4000:
		value |= DS1390_TRICKLE_CHARGER_4K_OHM;
		break;
	default:
		dev_warn(&spi->dev,
			 "Unsupported ohm value %02ux in dt\n", ohms);
		return;
	}

	ds1390_set_reg(&spi->dev, DS1390_REG_TRICKLE, value);

out:
	return;
}