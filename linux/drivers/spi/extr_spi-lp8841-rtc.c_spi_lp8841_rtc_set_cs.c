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
struct spi_lp8841_rtc {int /*<<< orphan*/  iomem; int /*<<< orphan*/  state; } ;
struct spi_device {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_LP8841_RTC_CE ; 
 struct spi_lp8841_rtc* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spi_lp8841_rtc_set_cs(struct spi_device *spi, bool enable)
{
	struct spi_lp8841_rtc *data = spi_master_get_devdata(spi->master);

	data->state = 0;
	writeb(data->state, data->iomem);
	if (enable) {
		usleep_range(4, 5);
		data->state |= SPI_LP8841_RTC_CE;
		writeb(data->state, data->iomem);
		usleep_range(4, 5);
	}
}