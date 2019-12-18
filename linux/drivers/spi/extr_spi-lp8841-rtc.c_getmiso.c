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
struct spi_lp8841_rtc {int /*<<< orphan*/  iomem; } ;

/* Variables and functions */
 int SPI_LP8841_RTC_MISO ; 
 int ioread8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
getmiso(struct spi_lp8841_rtc *data)
{
	return ioread8(data->iomem) & SPI_LP8841_RTC_MISO;
}