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
struct tinydrm_device {int dummy; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 struct tinydrm_device* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  tinydrm_shutdown (struct tinydrm_device*) ; 

__attribute__((used)) static void repaper_shutdown(struct spi_device *spi)
{
	struct tinydrm_device *tdev = spi_get_drvdata(spi);

	tinydrm_shutdown(tdev);
}