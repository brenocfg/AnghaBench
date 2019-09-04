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
typedef  int u32 ;
struct tmio_mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_VERSION ; 
 int /*<<< orphan*/  HOST_MODE ; 
#define  SDHI_VER_GEN2_SDR104 131 
#define  SDHI_VER_GEN2_SDR50 130 
#define  SDHI_VER_GEN3_SD 129 
#define  SDHI_VER_GEN3_SDMMC 128 
 int sd_ctrl_read16 (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_ctrl_write16 (struct tmio_mmc_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void renesas_sdhi_sdbuf_width(struct tmio_mmc_host *host, int width)
{
	u32 val;

	/*
	 * see also
	 *	renesas_sdhi_of_data :: dma_buswidth
	 */
	switch (sd_ctrl_read16(host, CTL_VERSION)) {
	case SDHI_VER_GEN2_SDR50:
		val = (width == 32) ? 0x0001 : 0x0000;
		break;
	case SDHI_VER_GEN2_SDR104:
		val = (width == 32) ? 0x0000 : 0x0001;
		break;
	case SDHI_VER_GEN3_SD:
	case SDHI_VER_GEN3_SDMMC:
		if (width == 64)
			val = 0x0000;
		else if (width == 32)
			val = 0x0101;
		else
			val = 0x0001;
		break;
	default:
		/* nothing to do */
		return;
	}

	sd_ctrl_write16(host, HOST_MODE, val);
}