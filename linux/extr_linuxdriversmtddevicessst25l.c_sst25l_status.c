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
struct sst25l_flash {int /*<<< orphan*/  spi; } ;
struct spi_transfer {unsigned char* tx_buf; unsigned char* rx_buf; int len; } ;
struct spi_message {int dummy; } ;
typedef  int /*<<< orphan*/  cmd_resp ;

/* Variables and functions */
 unsigned char SST25L_CMD_RDSR ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static int sst25l_status(struct sst25l_flash *flash, int *status)
{
	struct spi_message m;
	struct spi_transfer t;
	unsigned char cmd_resp[2];
	int err;

	spi_message_init(&m);
	memset(&t, 0, sizeof(struct spi_transfer));

	cmd_resp[0] = SST25L_CMD_RDSR;
	cmd_resp[1] = 0xff;
	t.tx_buf = cmd_resp;
	t.rx_buf = cmd_resp;
	t.len = sizeof(cmd_resp);
	spi_message_add_tail(&t, &m);
	err = spi_sync(flash->spi, &m);
	if (err < 0)
		return err;

	*status = cmd_resp[1];
	return 0;
}