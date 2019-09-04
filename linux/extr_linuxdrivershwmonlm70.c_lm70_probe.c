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
struct spi_device {int mode; int /*<<< orphan*/  modalias; int /*<<< orphan*/  dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct lm70 {int chip; struct spi_device* spi; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int driver_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 struct device* devm_hwmon_device_register_with_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct lm70*,int /*<<< orphan*/ ) ; 
 struct lm70* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm70_groups ; 
 int /*<<< orphan*/  lm70_of_ids ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* spi_get_device_id (struct spi_device*) ; 

__attribute__((used)) static int lm70_probe(struct spi_device *spi)
{
	const struct of_device_id *match;
	struct device *hwmon_dev;
	struct lm70 *p_lm70;
	int chip;

	match = of_match_device(lm70_of_ids, &spi->dev);
	if (match)
		chip = (int)(uintptr_t)match->data;
	else
		chip = spi_get_device_id(spi)->driver_data;

	/* signaling is SPI_MODE_0 */
	if (spi->mode & (SPI_CPOL | SPI_CPHA))
		return -EINVAL;

	/* NOTE:  we assume 8-bit words, and convert to 16 bits manually */

	p_lm70 = devm_kzalloc(&spi->dev, sizeof(*p_lm70), GFP_KERNEL);
	if (!p_lm70)
		return -ENOMEM;

	mutex_init(&p_lm70->lock);
	p_lm70->chip = chip;
	p_lm70->spi = spi;

	hwmon_dev = devm_hwmon_device_register_with_groups(&spi->dev,
							   spi->modalias,
							   p_lm70, lm70_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}