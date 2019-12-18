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
typedef  int u8 ;
typedef  int u32 ;
struct spi_transfer {int len; int* tx_buf; int* rx_buf; } ;
struct spi_message {int dummy; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (struct spi_device*,struct spi_message*) ; 

__attribute__((used)) static int cxd2880_spi_read_ts(struct spi_device *spi,
			       u8 *read_data,
			       u32 packet_num)
{
	int ret;
	u8 data[3];
	struct spi_message message;
	struct spi_transfer transfer[2] = {};

	if (!spi || !read_data || !packet_num) {
		pr_err("invalid arg\n");
		return -EINVAL;
	}
	if (packet_num > 0xffff) {
		pr_err("packet num > 0xffff\n");
		return -EINVAL;
	}

	data[0] = 0x10;
	data[1] = packet_num >> 8;
	data[2] = packet_num;

	spi_message_init(&message);

	transfer[0].len = 3;
	transfer[0].tx_buf = data;
	spi_message_add_tail(&transfer[0], &message);
	transfer[1].len = packet_num * 188;
	transfer[1].rx_buf = read_data;
	spi_message_add_tail(&transfer[1], &message);

	ret = spi_sync(spi, &message);
	if (ret)
		pr_err("spi_write_then_read failed\n");

	return ret;
}