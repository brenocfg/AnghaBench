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
struct madera {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  madera_dev_exit (struct madera*) ; 
 struct madera* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int madera_spi_remove(struct spi_device *spi)
{
	struct madera *madera = spi_get_drvdata(spi);

	madera_dev_exit(madera);

	return 0;
}