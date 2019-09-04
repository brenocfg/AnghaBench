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
typedef  void* u8 ;
struct st_sensor_transfer_buffer {int /*<<< orphan*/  buf_lock; void** tx_buf; } ;
struct spi_transfer {int bits_per_word; int len; void** tx_buf; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_sync_transfer (int /*<<< orphan*/ ,struct spi_transfer*,int) ; 
 int /*<<< orphan*/  to_spi_device (struct device*) ; 

__attribute__((used)) static int st_sensors_spi_write_byte(struct st_sensor_transfer_buffer *tb,
				struct device *dev, u8 reg_addr, u8 data)
{
	int err;

	struct spi_transfer xfers = {
		.tx_buf = tb->tx_buf,
		.bits_per_word = 8,
		.len = 2,
	};

	mutex_lock(&tb->buf_lock);
	tb->tx_buf[0] = reg_addr;
	tb->tx_buf[1] = data;

	err = spi_sync_transfer(to_spi_device(dev), &xfers, 1);
	mutex_unlock(&tb->buf_lock);

	return err;
}