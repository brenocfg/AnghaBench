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
typedef  int /*<<< orphan*/  uint8_t ;
struct fsi_master_gpio {int /*<<< orphan*/  dev; } ;
struct fsi_gpio_msg {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  FSI_CRC_ERR_RETRIES ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int poll_for_response (struct fsi_master_gpio*,int /*<<< orphan*/ ,size_t,void*) ; 
 int send_request (struct fsi_master_gpio*,struct fsi_gpio_msg*) ; 

__attribute__((used)) static int fsi_master_gpio_xfer(struct fsi_master_gpio *master, uint8_t slave,
		struct fsi_gpio_msg *cmd, size_t resp_len, void *resp)
{
	int rc = -EAGAIN, retries = 0;

	while ((retries++) < FSI_CRC_ERR_RETRIES) {
		rc = send_request(master, cmd);
		if (rc)
			break;
		rc = poll_for_response(master, slave, resp_len, resp);
		if (rc != -EAGAIN)
			break;
		rc = -EIO;
		dev_warn(master->dev, "ECRC retry %d\n", retries);

		/* Pace it a bit before retry */
		msleep(1);
	}

	return rc;
}