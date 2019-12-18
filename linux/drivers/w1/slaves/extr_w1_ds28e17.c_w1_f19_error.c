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
struct w1_slave {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t EAGAIN ; 
 size_t EIO ; 
 size_t ENXIO ; 
 int W1_F19_STATUS_ADDRESS ; 
 int W1_F19_STATUS_CRC ; 
 int W1_F19_STATUS_START ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static size_t w1_f19_error(struct w1_slave *sl, u8 w1_buf[])
{
	/* Warnings. */
	if (w1_buf[0] & W1_F19_STATUS_CRC)
		dev_warn(&sl->dev, "crc16 mismatch\n");
	if (w1_buf[0] & W1_F19_STATUS_ADDRESS)
		dev_warn(&sl->dev, "i2c device not responding\n");
	if ((w1_buf[0] & (W1_F19_STATUS_CRC | W1_F19_STATUS_ADDRESS)) == 0
			&& w1_buf[1] != 0) {
		dev_warn(&sl->dev, "i2c short write, %d bytes not acknowledged\n",
			w1_buf[1]);
	}

	/* Check error conditions. */
	if (w1_buf[0] & W1_F19_STATUS_ADDRESS)
		return -ENXIO;
	if (w1_buf[0] & W1_F19_STATUS_START)
		return -EAGAIN;
	if (w1_buf[0] != 0 || w1_buf[1] != 0)
		return -EIO;

	/* All ok. */
	return 0;
}