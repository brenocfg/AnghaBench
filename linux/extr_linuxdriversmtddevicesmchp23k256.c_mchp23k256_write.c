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
struct spi_transfer {unsigned char* tx_buf; size_t len; } ;
struct spi_message {int actual_length; } ;
struct mtd_info {int dummy; } ;
struct mchp23k256_flash {int /*<<< orphan*/  lock; int /*<<< orphan*/  spi; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  command ;

/* Variables and functions */
 int MAX_CMD_SIZE ; 
 unsigned char MCHP23K256_CMD_WRITE ; 
 int /*<<< orphan*/  mchp23k256_addr2cmd (struct mchp23k256_flash*,int /*<<< orphan*/ ,unsigned char*) ; 
 size_t mchp23k256_cmdsz (struct mchp23k256_flash*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 
 struct mchp23k256_flash* to_mchp23k256_flash (struct mtd_info*) ; 

__attribute__((used)) static int mchp23k256_write(struct mtd_info *mtd, loff_t to, size_t len,
			    size_t *retlen, const unsigned char *buf)
{
	struct mchp23k256_flash *flash = to_mchp23k256_flash(mtd);
	struct spi_transfer transfer[2] = {};
	struct spi_message message;
	unsigned char command[MAX_CMD_SIZE];
	int ret;

	spi_message_init(&message);

	command[0] = MCHP23K256_CMD_WRITE;
	mchp23k256_addr2cmd(flash, to, command);

	transfer[0].tx_buf = command;
	transfer[0].len = mchp23k256_cmdsz(flash);
	spi_message_add_tail(&transfer[0], &message);

	transfer[1].tx_buf = buf;
	transfer[1].len = len;
	spi_message_add_tail(&transfer[1], &message);

	mutex_lock(&flash->lock);

	ret = spi_sync(flash->spi, &message);

	mutex_unlock(&flash->lock);

	if (ret)
		return ret;

	if (retlen && message.actual_length > sizeof(command))
		*retlen += message.actual_length - sizeof(command);

	return 0;
}