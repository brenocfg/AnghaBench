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
struct cros_ec_device {int dummy; } ;

/* Variables and functions */
 int cros_ec_unregister (struct cros_ec_device*) ; 
 struct cros_ec_device* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int cros_ec_spi_remove(struct spi_device *spi)
{
	struct cros_ec_device *ec_dev = spi_get_drvdata(spi);

	return cros_ec_unregister(ec_dev);
}