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
struct arizona {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arizona_dev_exit (struct arizona*) ; 
 struct arizona* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int arizona_spi_remove(struct spi_device *spi)
{
	struct arizona *arizona = spi_get_drvdata(spi);

	arizona_dev_exit(arizona);

	return 0;
}