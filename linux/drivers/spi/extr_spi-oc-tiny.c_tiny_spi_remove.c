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
struct TYPE_2__ {struct spi_master* master; } ;
struct tiny_spi {unsigned int gpio_cs_count; int /*<<< orphan*/ * gpio_cs; TYPE_1__ bitbang; } ;
struct spi_master {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 struct tiny_spi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spi_bitbang_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 

__attribute__((used)) static int tiny_spi_remove(struct platform_device *pdev)
{
	struct tiny_spi *hw = platform_get_drvdata(pdev);
	struct spi_master *master = hw->bitbang.master;
	unsigned int i;

	spi_bitbang_stop(&hw->bitbang);
	for (i = 0; i < hw->gpio_cs_count; i++)
		gpio_free(hw->gpio_cs[i]);
	spi_master_put(master);
	return 0;
}