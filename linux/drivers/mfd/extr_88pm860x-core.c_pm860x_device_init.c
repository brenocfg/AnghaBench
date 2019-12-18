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
struct pm860x_platform_data {int dummy; } ;
struct pm860x_chip {int id; scalar_t__ companion; scalar_t__ client; scalar_t__ core_irq; } ;

/* Variables and functions */
#define  CHIP_PM8606 129 
#define  CHIP_PM8607 128 
 int /*<<< orphan*/  device_8606_init (struct pm860x_chip*,scalar_t__,struct pm860x_platform_data*) ; 
 int /*<<< orphan*/  device_8607_init (struct pm860x_chip*,scalar_t__,struct pm860x_platform_data*) ; 

__attribute__((used)) static int pm860x_device_init(struct pm860x_chip *chip,
					struct pm860x_platform_data *pdata)
{
	chip->core_irq = 0;

	switch (chip->id) {
	case CHIP_PM8606:
		device_8606_init(chip, chip->client, pdata);
		break;
	case CHIP_PM8607:
		device_8607_init(chip, chip->client, pdata);
		break;
	}

	if (chip->companion) {
		switch (chip->id) {
		case CHIP_PM8607:
			device_8606_init(chip, chip->companion, pdata);
			break;
		case CHIP_PM8606:
			device_8607_init(chip, chip->companion, pdata);
			break;
		}
	}

	return 0;
}