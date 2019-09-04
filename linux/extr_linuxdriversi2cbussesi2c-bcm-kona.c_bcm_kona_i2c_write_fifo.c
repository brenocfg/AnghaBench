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
struct i2c_msg {unsigned int len; int /*<<< orphan*/ * buf; } ;
struct bcm_kona_i2c_dev {int dummy; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 unsigned int MAX_TX_FIFO_SIZE ; 
 int bcm_kona_i2c_write_fifo_single (struct bcm_kona_i2c_dev*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int bcm_kona_i2c_write_fifo(struct bcm_kona_i2c_dev *dev,
				   struct i2c_msg *msg)
{
	unsigned int bytes_to_write = MAX_TX_FIFO_SIZE;
	unsigned int bytes_written = 0;
	int rc;

	uint8_t *tmp_buf = msg->buf;

	while (bytes_written < msg->len) {
		if (msg->len - bytes_written <= MAX_TX_FIFO_SIZE)
			bytes_to_write = msg->len - bytes_written;

		rc = bcm_kona_i2c_write_fifo_single(dev, tmp_buf,
						    bytes_to_write);
		if (rc < 0)
			return -EREMOTEIO;

		bytes_written += bytes_to_write;
		tmp_buf += bytes_to_write;
	}

	return 0;
}