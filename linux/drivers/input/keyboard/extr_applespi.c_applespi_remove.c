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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct applespi_data {int /*<<< orphan*/  debugfs_root; int /*<<< orphan*/  gpe; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_disable_gpe (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_remove_gpe_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  applespi_drain_reads (struct applespi_data*) ; 
 int /*<<< orphan*/  applespi_drain_writes (struct applespi_data*) ; 
 int /*<<< orphan*/  applespi_notify ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_wakeup_disable (int /*<<< orphan*/ *) ; 
 struct applespi_data* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int applespi_remove(struct spi_device *spi)
{
	struct applespi_data *applespi = spi_get_drvdata(spi);

	applespi_drain_writes(applespi);

	acpi_disable_gpe(NULL, applespi->gpe);
	acpi_remove_gpe_handler(NULL, applespi->gpe, applespi_notify);
	device_wakeup_disable(&spi->dev);

	applespi_drain_reads(applespi);

	debugfs_remove_recursive(applespi->debugfs_root);

	return 0;
}