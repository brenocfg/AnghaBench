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
typedef  int /*<<< orphan*/  u8 ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spi_write (struct spi_device*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void repaper_spi_mosi_low(struct spi_device *spi)
{
	const u8 buf[1] = { 0 };

	spi_write(spi, buf, 1);
}