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
struct mipi_dbi {int /*<<< orphan*/  tinydrm; } ;

/* Variables and functions */
 struct mipi_dbi* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  tinydrm_shutdown (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ili9225_shutdown(struct spi_device *spi)
{
	struct mipi_dbi *mipi = spi_get_drvdata(spi);

	tinydrm_shutdown(&mipi->tinydrm);
}