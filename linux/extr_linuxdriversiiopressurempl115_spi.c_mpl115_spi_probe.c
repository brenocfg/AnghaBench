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
struct spi_device_id {int /*<<< orphan*/  name; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int mpl115_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpl115_spi_ops ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 

__attribute__((used)) static int mpl115_spi_probe(struct spi_device *spi)
{
	const struct spi_device_id *id = spi_get_device_id(spi);

	return mpl115_probe(&spi->dev, id->name, &mpl115_spi_ops);
}