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
struct txx9spi {int /*<<< orphan*/  clk; int /*<<< orphan*/  work; } ;
struct spi_master {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 struct spi_master* platform_get_drvdata (struct platform_device*) ; 
 struct txx9spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int txx9spi_remove(struct platform_device *dev)
{
	struct spi_master *master = platform_get_drvdata(dev);
	struct txx9spi *c = spi_master_get_devdata(master);

	flush_work(&c->work);
	clk_disable_unprepare(c->clk);
	return 0;
}