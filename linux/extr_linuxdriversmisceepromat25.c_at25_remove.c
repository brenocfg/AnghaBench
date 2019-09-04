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
struct at25_data {int /*<<< orphan*/  nvmem; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvmem_unregister (int /*<<< orphan*/ ) ; 
 struct at25_data* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int at25_remove(struct spi_device *spi)
{
	struct at25_data	*at25;

	at25 = spi_get_drvdata(spi);
	nvmem_unregister(at25->nvmem);

	return 0;
}