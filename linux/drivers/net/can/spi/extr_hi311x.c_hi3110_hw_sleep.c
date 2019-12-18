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
 int /*<<< orphan*/  HI3110_CTRL0_SLEEP_MODE ; 
 int /*<<< orphan*/  HI3110_WRITE_CTRL0 ; 
 int /*<<< orphan*/  hi3110_write (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hi3110_hw_sleep(struct spi_device *spi)
{
	hi3110_write(spi, HI3110_WRITE_CTRL0, HI3110_CTRL0_SLEEP_MODE);
}