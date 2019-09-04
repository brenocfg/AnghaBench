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
struct spi_device {int dummy; } ;
struct fpga_data {int /*<<< orphan*/  fw_loaded; } ;

/* Variables and functions */
 struct fpga_data* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lattice_ecp3_remove(struct spi_device *spi)
{
	struct fpga_data *data = spi_get_drvdata(spi);

	wait_for_completion(&data->fw_loaded);

	return 0;
}