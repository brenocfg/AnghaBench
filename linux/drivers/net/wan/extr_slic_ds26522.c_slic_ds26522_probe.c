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
struct spi_device {int bits_per_word; int /*<<< orphan*/  chip_select; } ;

/* Variables and functions */
 struct spi_device* g_spi ; 
 int /*<<< orphan*/  get_slic_product_code (struct spi_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int slic_ds26522_init_configure (struct spi_device*) ; 

__attribute__((used)) static int slic_ds26522_probe(struct spi_device *spi)
{
	int ret = 0;

	g_spi = spi;
	spi->bits_per_word = 8;

	if (!get_slic_product_code(spi))
		return ret;

	ret = slic_ds26522_init_configure(spi);
	if (ret == 0)
		pr_info("DS26522 cs%d configured\n", spi->chip_select);

	return ret;
}