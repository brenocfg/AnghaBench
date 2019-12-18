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
struct spi_mpc8xxx_cs {int dummy; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct spi_mpc8xxx_cs*) ; 
 struct spi_mpc8xxx_cs* spi_get_ctldata (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_ctldata (struct spi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fsl_spi_cleanup(struct spi_device *spi)
{
	struct spi_mpc8xxx_cs *cs = spi_get_ctldata(spi);

	kfree(cs);
	spi_set_ctldata(spi, NULL);
}