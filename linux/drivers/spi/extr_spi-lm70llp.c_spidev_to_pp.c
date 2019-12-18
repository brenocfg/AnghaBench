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
struct spi_lm70llp {int dummy; } ;
struct spi_device {struct spi_lm70llp* controller_data; } ;

/* Variables and functions */

__attribute__((used)) static inline struct spi_lm70llp *spidev_to_pp(struct spi_device *spi)
{
	return spi->controller_data;
}