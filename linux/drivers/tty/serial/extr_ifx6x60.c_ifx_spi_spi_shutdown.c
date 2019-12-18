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
struct ifx_spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ifx_modem_power_off (struct ifx_spi_device*) ; 
 struct ifx_spi_device* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static void ifx_spi_spi_shutdown(struct spi_device *spi)
{
	struct ifx_spi_device *ifx_dev = spi_get_drvdata(spi);

	ifx_modem_power_off(ifx_dev);
}