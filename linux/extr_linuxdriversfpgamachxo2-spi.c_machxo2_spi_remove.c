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
struct fpga_manager {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fpga_mgr_unregister (struct fpga_manager*) ; 
 struct fpga_manager* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int machxo2_spi_remove(struct spi_device *spi)
{
	struct fpga_manager *mgr = spi_get_drvdata(spi);

	fpga_mgr_unregister(mgr);

	return 0;
}