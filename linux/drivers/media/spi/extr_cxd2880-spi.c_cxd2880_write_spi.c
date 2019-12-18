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
typedef  int /*<<< orphan*/  u32 ;
struct spi_transfer {int /*<<< orphan*/  len; int /*<<< orphan*/ * tx_buf; } ;
struct spi_message {int dummy; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (struct spi_device*,struct spi_message*) ; 

__attribute__((used)) static int cxd2880_write_spi(struct spi_device *spi, u8 *data, u32 size)
{
	struct spi_message msg;
	struct spi_transfer tx = {};

	if (!spi || !data) {
		pr_err("invalid arg\n");
		return -EINVAL;
	}

	tx.tx_buf = data;
	tx.len = size;

	spi_message_init(&msg);
	spi_message_add_tail(&tx, &msg);

	return spi_sync(spi, &msg);
}