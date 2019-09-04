#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tmio_mmc_host {TYPE_1__* pdata; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
#define  CTL_DMA_ENABLE 136 
#define  CTL_SD_CARD_CLK_CTL 135 
#define  CTL_SD_CMD 134 
#define  CTL_SD_MEM_CARD_OPT 133 
#define  CTL_SD_XFER_LEN 132 
#define  CTL_STOP_INTERNAL_ACTION 131 
#define  CTL_TRANSACTION_CTL 130 
#define  CTL_XFER_BLK_COUNT 129 
#define  HOST_MODE 128 
 int TMIO_MMC_HAVE_CBSY ; 
 int /*<<< orphan*/  TMIO_STAT_CMD_BUSY ; 
 int /*<<< orphan*/  TMIO_STAT_SCLKDIVEN ; 
 int renesas_sdhi_wait_idle (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int renesas_sdhi_write16_hook(struct tmio_mmc_host *host, int addr)
{
	u32 bit = TMIO_STAT_SCLKDIVEN;

	switch (addr) {
	case CTL_SD_CMD:
	case CTL_STOP_INTERNAL_ACTION:
	case CTL_XFER_BLK_COUNT:
	case CTL_SD_XFER_LEN:
	case CTL_SD_MEM_CARD_OPT:
	case CTL_TRANSACTION_CTL:
	case CTL_DMA_ENABLE:
	case HOST_MODE:
		if (host->pdata->flags & TMIO_MMC_HAVE_CBSY)
			bit = TMIO_STAT_CMD_BUSY;
		/* fallthrough */
	case CTL_SD_CARD_CLK_CTL:
		return renesas_sdhi_wait_idle(host, bit);
	}

	return 0;
}