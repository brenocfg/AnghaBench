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
typedef  int /*<<< orphan*/  u16 ;
struct rtsx_usb_sdmmc {scalar_t__ initial_mode; } ;
struct mmc_request {struct mmc_data* data; struct mmc_command* cmd; } ;
struct mmc_data {int flags; scalar_t__ blksz; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct mmc_command {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_disable_initial_mode (struct rtsx_usb_sdmmc*) ; 
 int /*<<< orphan*/  sd_enable_initial_mode (struct rtsx_usb_sdmmc*) ; 
 int /*<<< orphan*/  sd_read_data (struct rtsx_usb_sdmmc*,struct mmc_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  sd_write_data (struct rtsx_usb_sdmmc*,struct mmc_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  sg_copy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void sd_normal_rw(struct rtsx_usb_sdmmc *host,
		struct mmc_request *mrq)
{
	struct mmc_command *cmd = mrq->cmd;
	struct mmc_data *data = mrq->data;
	u8 *buf;

	buf = kzalloc(data->blksz, GFP_NOIO);
	if (!buf) {
		cmd->error = -ENOMEM;
		return;
	}

	if (data->flags & MMC_DATA_READ) {
		if (host->initial_mode)
			sd_disable_initial_mode(host);

		cmd->error = sd_read_data(host, cmd, (u16)data->blksz, buf,
				data->blksz, 200);

		if (host->initial_mode)
			sd_enable_initial_mode(host);

		sg_copy_from_buffer(data->sg, data->sg_len, buf, data->blksz);
	} else {
		sg_copy_to_buffer(data->sg, data->sg_len, buf, data->blksz);

		cmd->error = sd_write_data(host, cmd, (u16)data->blksz, buf,
				data->blksz, 200);
	}

	kfree(buf);
}