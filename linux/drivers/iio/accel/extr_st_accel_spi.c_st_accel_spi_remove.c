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

/* Variables and functions */
 int /*<<< orphan*/  spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  st_accel_common_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_accel_spi_remove(struct spi_device *spi)
{
	st_accel_common_remove(spi_get_drvdata(spi));

	return 0;
}