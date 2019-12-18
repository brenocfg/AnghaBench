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
struct adxl34x {int dummy; } ;

/* Variables and functions */
 int adxl34x_remove (struct adxl34x*) ; 
 struct adxl34x* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int adxl34x_spi_remove(struct spi_device *spi)
{
	struct adxl34x *ac = spi_get_drvdata(spi);

	return adxl34x_remove(ac);
}