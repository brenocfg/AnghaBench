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
typedef  int u16 ;
struct spi_transfer {int* tx_buf; int len; int delay_usecs; int* rx_buf; } ;
struct spi_message {int dummy; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (struct spi_device*,struct spi_message*) ; 

__attribute__((used)) static int gs_read_register(struct spi_device *spi, u16 addr, u16 *value)
{
	int ret;
	u16 buf_addr = (0x8000 | (0x0FFF & addr));
	u16 buf_value = 0;
	struct spi_message msg;
	struct spi_transfer tx[] = {
		{
			.tx_buf = &buf_addr,
			.len = 2,
			.delay_usecs = 1,
		}, {
			.rx_buf = &buf_value,
			.len = 2,
			.delay_usecs = 1,
		},
	};

	spi_message_init(&msg);
	spi_message_add_tail(&tx[0], &msg);
	spi_message_add_tail(&tx[1], &msg);
	ret = spi_sync(spi, &msg);

	*value = buf_value;

	return ret;
}