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
 unsigned int MAX_RX_FIFO_SIZE ; 
 int bcm_kona_i2c_read_fifo_single (struct bcm_kona_i2c_dev*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

__attribute__((used)) static int bcm_kona_i2c_read_fifo(struct bcm_kona_i2c_dev *dev,
				  struct i2c_msg *msg)
{
	unsigned int bytes_to_read = MAX_RX_FIFO_SIZE;
	unsigned int last_byte_nak = 0;
	unsigned int bytes_read = 0;
	int rc;

	uint8_t *tmp_buf = msg->buf;

	while (bytes_read < msg->len) {
		if (msg->len - bytes_read <= MAX_RX_FIFO_SIZE) {
			last_byte_nak = 1; /* NAK last byte of transfer */
			bytes_to_read = msg->len - bytes_read;
		}

		rc = bcm_kona_i2c_read_fifo_single(dev, tmp_buf, bytes_to_read,
						   last_byte_nak);
		if (rc < 0)
			return -EREMOTEIO;

		bytes_read += bytes_to_read;
		tmp_buf += bytes_to_read;
	}

	return 0;
}