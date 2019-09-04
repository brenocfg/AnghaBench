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
typedef  unsigned char u8 ;
struct rtsx_usb_sdmmc {int /*<<< orphan*/  ucr; } ;

/* Variables and functions */
#define  MMC_BUS_WIDTH_1 133 
#define  MMC_BUS_WIDTH_4 132 
#define  MMC_BUS_WIDTH_8 131 
#define  SD_BUS_WIDTH_1BIT 130 
#define  SD_BUS_WIDTH_4BIT 129 
#define  SD_BUS_WIDTH_8BIT 128 
 int /*<<< orphan*/  SD_CFG1 ; 
 int rtsx_usb_write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char const) ; 

__attribute__((used)) static int sd_set_bus_width(struct rtsx_usb_sdmmc *host,
		unsigned char bus_width)
{
	int err = 0;
	static const u8 width[] = {
		[MMC_BUS_WIDTH_1] = SD_BUS_WIDTH_1BIT,
		[MMC_BUS_WIDTH_4] = SD_BUS_WIDTH_4BIT,
		[MMC_BUS_WIDTH_8] = SD_BUS_WIDTH_8BIT,
	};

	if (bus_width <= MMC_BUS_WIDTH_8)
		err = rtsx_usb_write_register(host->ucr, SD_CFG1,
				0x03, width[bus_width]);

	return err;
}