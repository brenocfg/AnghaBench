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
struct sprd_adi {int /*<<< orphan*/  restart_handler; } ;
struct spi_controller {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct spi_controller* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 struct sprd_adi* spi_controller_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  unregister_restart_handler (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sprd_adi_remove(struct platform_device *pdev)
{
	struct spi_controller *ctlr = dev_get_drvdata(&pdev->dev);
	struct sprd_adi *sadi = spi_controller_get_devdata(ctlr);

	unregister_restart_handler(&sadi->restart_handler);
	return 0;
}