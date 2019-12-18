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
typedef  int u8 ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct ca8210_platform_data {int extclockfreq; int extclockgpio; } ;

/* Variables and functions */
#define  EIGHT_MHZ 132 
 int EINVAL ; 
#define  FOUR_MHZ 131 
 int /*<<< orphan*/  HWME_SYSCLKOUT ; 
#define  ONE_MHZ 130 
#define  SIXTEEN_MHZ 129 
#define  TWO_MHZ 128 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hwme_set_request_sync (int /*<<< orphan*/ ,int,int*,struct spi_device*) ; 
 int link_to_linux_err (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ca8210_config_extern_clk(
	struct ca8210_platform_data *pdata,
	struct spi_device *spi,
	bool on
)
{
	u8 clkparam[2];

	if (on) {
		dev_info(&spi->dev, "Switching external clock on\n");
		switch (pdata->extclockfreq) {
		case SIXTEEN_MHZ:
			clkparam[0] = 1;
			break;
		case EIGHT_MHZ:
			clkparam[0] = 2;
			break;
		case FOUR_MHZ:
			clkparam[0] = 3;
			break;
		case TWO_MHZ:
			clkparam[0] = 4;
			break;
		case ONE_MHZ:
			clkparam[0] = 5;
			break;
		default:
			dev_crit(&spi->dev, "Invalid extclock-freq\n");
			return -EINVAL;
		}
		clkparam[1] = pdata->extclockgpio;
	} else {
		dev_info(&spi->dev, "Switching external clock off\n");
		clkparam[0] = 0; /* off */
		clkparam[1] = 0;
	}
	return link_to_linux_err(
		hwme_set_request_sync(HWME_SYSCLKOUT, 2, clkparam, spi)
	);
}