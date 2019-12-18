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
typedef  void* u8 ;
typedef  int u32 ;
struct mmc_ios {int clock; int vdd; scalar_t__ bus_mode; int power_mode; int bus_width; int timing; int signal_voltage; int drv_type; } ;
struct mmc_host {int /*<<< orphan*/  ios; } ;
struct gb_sdio_set_ios_request {void* drv_type; void* signal_voltage; void* timing; void* bus_width; void* power_mode; int /*<<< orphan*/  bus_mode; void* vdd; void* clock; } ;
struct gb_sdio_host {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_SDIO_BUSMODE_OPENDRAIN ; 
 int /*<<< orphan*/  GB_SDIO_BUSMODE_PUSHPULL ; 
 void* GB_SDIO_BUS_WIDTH_1 ; 
 void* GB_SDIO_BUS_WIDTH_4 ; 
 void* GB_SDIO_BUS_WIDTH_8 ; 
 void* GB_SDIO_POWER_OFF ; 
 void* GB_SDIO_POWER_ON ; 
 void* GB_SDIO_POWER_UNDEFINED ; 
 void* GB_SDIO_POWER_UP ; 
 void* GB_SDIO_SET_DRIVER_TYPE_A ; 
 void* GB_SDIO_SET_DRIVER_TYPE_B ; 
 void* GB_SDIO_SET_DRIVER_TYPE_C ; 
 void* GB_SDIO_SET_DRIVER_TYPE_D ; 
 void* GB_SDIO_SIGNAL_VOLTAGE_120 ; 
 void* GB_SDIO_SIGNAL_VOLTAGE_180 ; 
 void* GB_SDIO_SIGNAL_VOLTAGE_330 ; 
 void* GB_SDIO_TIMING_LEGACY ; 
 void* GB_SDIO_TIMING_MMC_DDR52 ; 
 void* GB_SDIO_TIMING_MMC_HS ; 
 void* GB_SDIO_TIMING_MMC_HS200 ; 
 void* GB_SDIO_TIMING_MMC_HS400 ; 
 void* GB_SDIO_TIMING_SD_HS ; 
 void* GB_SDIO_TIMING_UHS_DDR50 ; 
 void* GB_SDIO_TIMING_UHS_SDR104 ; 
 void* GB_SDIO_TIMING_UHS_SDR12 ; 
 void* GB_SDIO_TIMING_UHS_SDR25 ; 
 void* GB_SDIO_TIMING_UHS_SDR50 ; 
 int GB_SDIO_VDD_SHIFT ; 
 scalar_t__ MMC_BUSMODE_OPENDRAIN ; 
#define  MMC_BUS_WIDTH_1 152 
#define  MMC_BUS_WIDTH_4 151 
#define  MMC_BUS_WIDTH_8 150 
#define  MMC_POWER_OFF 149 
#define  MMC_POWER_ON 148 
#define  MMC_POWER_UNDEFINED 147 
#define  MMC_POWER_UP 146 
#define  MMC_SET_DRIVER_TYPE_A 145 
#define  MMC_SET_DRIVER_TYPE_B 144 
#define  MMC_SET_DRIVER_TYPE_C 143 
#define  MMC_SET_DRIVER_TYPE_D 142 
#define  MMC_SIGNAL_VOLTAGE_120 141 
#define  MMC_SIGNAL_VOLTAGE_180 140 
#define  MMC_SIGNAL_VOLTAGE_330 139 
#define  MMC_TIMING_LEGACY 138 
#define  MMC_TIMING_MMC_DDR52 137 
#define  MMC_TIMING_MMC_HS 136 
#define  MMC_TIMING_MMC_HS200 135 
#define  MMC_TIMING_MMC_HS400 134 
#define  MMC_TIMING_SD_HS 133 
#define  MMC_TIMING_UHS_DDR50 132 
#define  MMC_TIMING_UHS_SDR104 131 
#define  MMC_TIMING_UHS_SDR12 130 
#define  MMC_TIMING_UHS_SDR25 129 
#define  MMC_TIMING_UHS_SDR50 128 
 void* cpu_to_le32 (int) ; 
 int gb_sdio_set_ios (struct gb_sdio_host*,struct gb_sdio_set_ios_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mmc_ios*,int) ; 
 struct gb_sdio_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gb_mmc_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct gb_sdio_host *host = mmc_priv(mmc);
	struct gb_sdio_set_ios_request request;
	int ret;
	u8 power_mode;
	u8 bus_width;
	u8 timing;
	u8 signal_voltage;
	u8 drv_type;
	u32 vdd = 0;

	mutex_lock(&host->lock);
	request.clock = cpu_to_le32(ios->clock);

	if (ios->vdd)
		vdd = 1 << (ios->vdd - GB_SDIO_VDD_SHIFT);
	request.vdd = cpu_to_le32(vdd);

	request.bus_mode = ios->bus_mode == MMC_BUSMODE_OPENDRAIN ?
			    GB_SDIO_BUSMODE_OPENDRAIN :
			    GB_SDIO_BUSMODE_PUSHPULL;

	switch (ios->power_mode) {
	case MMC_POWER_OFF:
	default:
		power_mode = GB_SDIO_POWER_OFF;
		break;
	case MMC_POWER_UP:
		power_mode = GB_SDIO_POWER_UP;
		break;
	case MMC_POWER_ON:
		power_mode = GB_SDIO_POWER_ON;
		break;
	case MMC_POWER_UNDEFINED:
		power_mode = GB_SDIO_POWER_UNDEFINED;
		break;
	}
	request.power_mode = power_mode;

	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_1:
		bus_width = GB_SDIO_BUS_WIDTH_1;
		break;
	case MMC_BUS_WIDTH_4:
	default:
		bus_width = GB_SDIO_BUS_WIDTH_4;
		break;
	case MMC_BUS_WIDTH_8:
		bus_width = GB_SDIO_BUS_WIDTH_8;
		break;
	}
	request.bus_width = bus_width;

	switch (ios->timing) {
	case MMC_TIMING_LEGACY:
	default:
		timing = GB_SDIO_TIMING_LEGACY;
		break;
	case MMC_TIMING_MMC_HS:
		timing = GB_SDIO_TIMING_MMC_HS;
		break;
	case MMC_TIMING_SD_HS:
		timing = GB_SDIO_TIMING_SD_HS;
		break;
	case MMC_TIMING_UHS_SDR12:
		timing = GB_SDIO_TIMING_UHS_SDR12;
		break;
	case MMC_TIMING_UHS_SDR25:
		timing = GB_SDIO_TIMING_UHS_SDR25;
		break;
	case MMC_TIMING_UHS_SDR50:
		timing = GB_SDIO_TIMING_UHS_SDR50;
		break;
	case MMC_TIMING_UHS_SDR104:
		timing = GB_SDIO_TIMING_UHS_SDR104;
		break;
	case MMC_TIMING_UHS_DDR50:
		timing = GB_SDIO_TIMING_UHS_DDR50;
		break;
	case MMC_TIMING_MMC_DDR52:
		timing = GB_SDIO_TIMING_MMC_DDR52;
		break;
	case MMC_TIMING_MMC_HS200:
		timing = GB_SDIO_TIMING_MMC_HS200;
		break;
	case MMC_TIMING_MMC_HS400:
		timing = GB_SDIO_TIMING_MMC_HS400;
		break;
	}
	request.timing = timing;

	switch (ios->signal_voltage) {
	case MMC_SIGNAL_VOLTAGE_330:
		signal_voltage = GB_SDIO_SIGNAL_VOLTAGE_330;
		break;
	case MMC_SIGNAL_VOLTAGE_180:
	default:
		signal_voltage = GB_SDIO_SIGNAL_VOLTAGE_180;
		break;
	case MMC_SIGNAL_VOLTAGE_120:
		signal_voltage = GB_SDIO_SIGNAL_VOLTAGE_120;
		break;
	}
	request.signal_voltage = signal_voltage;

	switch (ios->drv_type) {
	case MMC_SET_DRIVER_TYPE_A:
		drv_type = GB_SDIO_SET_DRIVER_TYPE_A;
		break;
	case MMC_SET_DRIVER_TYPE_C:
		drv_type = GB_SDIO_SET_DRIVER_TYPE_C;
		break;
	case MMC_SET_DRIVER_TYPE_D:
		drv_type = GB_SDIO_SET_DRIVER_TYPE_D;
		break;
	case MMC_SET_DRIVER_TYPE_B:
	default:
		drv_type = GB_SDIO_SET_DRIVER_TYPE_B;
		break;
	}
	request.drv_type = drv_type;

	ret = gb_sdio_set_ios(host, &request);
	if (ret < 0)
		goto out;

	memcpy(&mmc->ios, ios, sizeof(mmc->ios));

out:
	mutex_unlock(&host->lock);
}