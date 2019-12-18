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
struct device {struct mmc_spi_platform_data* platform_data; struct device_node* of_node; } ;
struct spi_device {struct device dev; } ;
struct mmc_spi_platform_data {int /*<<< orphan*/  caps; int /*<<< orphan*/  exit; int /*<<< orphan*/  init; int /*<<< orphan*/  ocr_mask; } ;
struct of_mmc_spi {scalar_t__ detect_irq; struct mmc_spi_platform_data pdata; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MMC_CAP_NEEDS_POLL ; 
 scalar_t__ irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct of_mmc_spi*) ; 
 struct of_mmc_spi* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mmc_of_parse_voltage (struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_mmc_spi_exit ; 
 int /*<<< orphan*/  of_mmc_spi_init ; 

struct mmc_spi_platform_data *mmc_spi_get_pdata(struct spi_device *spi)
{
	struct device *dev = &spi->dev;
	struct device_node *np = dev->of_node;
	struct of_mmc_spi *oms;

	if (dev->platform_data || !np)
		return dev->platform_data;

	oms = kzalloc(sizeof(*oms), GFP_KERNEL);
	if (!oms)
		return NULL;

	if (mmc_of_parse_voltage(np, &oms->pdata.ocr_mask) <= 0)
		goto err_ocr;

	oms->detect_irq = irq_of_parse_and_map(np, 0);
	if (oms->detect_irq != 0) {
		oms->pdata.init = of_mmc_spi_init;
		oms->pdata.exit = of_mmc_spi_exit;
	} else {
		oms->pdata.caps |= MMC_CAP_NEEDS_POLL;
	}

	dev->platform_data = &oms->pdata;
	return dev->platform_data;
err_ocr:
	kfree(oms);
	return NULL;
}