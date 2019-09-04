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

/* Variables and functions */
 int kxsd9_common_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kxsd9_spi_remove(struct spi_device *spi)
{
	return kxsd9_common_remove(&spi->dev);
}