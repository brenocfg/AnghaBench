#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct tmio_mmc_host {TYPE_2__* pdata; TYPE_1__* data; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_SD_DATA_PORT ; 
 int MMC_DATA_READ ; 
 int TMIO_MMC_32BIT_DATA_PORT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int sd_ctrl_read16 (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_ctrl_read16_rep (struct tmio_mmc_host*,int /*<<< orphan*/ ,unsigned short*,unsigned int) ; 
 int /*<<< orphan*/  sd_ctrl_read32_rep (struct tmio_mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sd_ctrl_write16 (struct tmio_mmc_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sd_ctrl_write16_rep (struct tmio_mmc_host*,int /*<<< orphan*/ ,unsigned short*,unsigned int) ; 
 int /*<<< orphan*/  sd_ctrl_write32_rep (struct tmio_mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void tmio_mmc_transfer_data(struct tmio_mmc_host *host,
				   unsigned short *buf,
				   unsigned int count)
{
	int is_read = host->data->flags & MMC_DATA_READ;
	u8  *buf8;

	/*
	 * Transfer the data
	 */
	if (host->pdata->flags & TMIO_MMC_32BIT_DATA_PORT) {
		u32 data = 0;
		u32 *buf32 = (u32 *)buf;

		if (is_read)
			sd_ctrl_read32_rep(host, CTL_SD_DATA_PORT, buf32,
					   count >> 2);
		else
			sd_ctrl_write32_rep(host, CTL_SD_DATA_PORT, buf32,
					    count >> 2);

		/* if count was multiple of 4 */
		if (!(count & 0x3))
			return;

		buf32 += count >> 2;
		count %= 4;

		if (is_read) {
			sd_ctrl_read32_rep(host, CTL_SD_DATA_PORT, &data, 1);
			memcpy(buf32, &data, count);
		} else {
			memcpy(&data, buf32, count);
			sd_ctrl_write32_rep(host, CTL_SD_DATA_PORT, &data, 1);
		}

		return;
	}

	if (is_read)
		sd_ctrl_read16_rep(host, CTL_SD_DATA_PORT, buf, count >> 1);
	else
		sd_ctrl_write16_rep(host, CTL_SD_DATA_PORT, buf, count >> 1);

	/* if count was even number */
	if (!(count & 0x1))
		return;

	/* if count was odd number */
	buf8 = (u8 *)(buf + (count >> 1));

	/*
	 * FIXME
	 *
	 * driver and this function are assuming that
	 * it is used as little endian
	 */
	if (is_read)
		*buf8 = sd_ctrl_read16(host, CTL_SD_DATA_PORT) & 0xff;
	else
		sd_ctrl_write16(host, CTL_SD_DATA_PORT, *buf8);
}