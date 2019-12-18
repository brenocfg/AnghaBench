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
struct spi_controller {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mt7621_spi {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct spi_controller* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 struct mt7621_spi* spi_controller_get_devdata (struct spi_controller*) ; 

__attribute__((used)) static int mt7621_spi_remove(struct platform_device *pdev)
{
	struct spi_controller *master;
	struct mt7621_spi *rs;

	master = dev_get_drvdata(&pdev->dev);
	rs = spi_controller_get_devdata(master);

	clk_disable_unprepare(rs->clk);

	return 0;
}