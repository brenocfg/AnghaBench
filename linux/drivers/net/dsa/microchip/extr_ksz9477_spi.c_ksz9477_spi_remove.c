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
struct ksz_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ksz_switch_remove (struct ksz_device*) ; 
 struct ksz_device* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int ksz9477_spi_remove(struct spi_device *spi)
{
	struct ksz_device *dev = spi_get_drvdata(spi);

	if (dev)
		ksz_switch_remove(dev);

	return 0;
}