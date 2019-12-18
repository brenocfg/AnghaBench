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
struct i2c_au1550_data {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PSC_SMBTXRX ; 
 int /*<<< orphan*/  PSC_SMBTXRX_STP ; 
 int RD (struct i2c_au1550_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR (struct i2c_au1550_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_rx_byte (struct i2c_au1550_data*,unsigned char*) ; 
 scalar_t__ wait_master_done (struct i2c_au1550_data*) ; 

__attribute__((used)) static int i2c_read(struct i2c_au1550_data *adap, unsigned char *buf,
		    unsigned int len)
{
	int i;

	if (len == 0)
		return 0;

	/* A read is performed by stuffing the transmit fifo with
	 * zero bytes for timing, waiting for bytes to appear in the
	 * receive fifo, then reading the bytes.
	 */
	i = 0;
	while (i < (len - 1)) {
		WR(adap, PSC_SMBTXRX, 0);
		if (wait_for_rx_byte(adap, &buf[i]))
			return -EIO;

		i++;
	}

	/* The last byte has to indicate transfer done. */
	WR(adap, PSC_SMBTXRX, PSC_SMBTXRX_STP);
	if (wait_master_done(adap))
		return -EIO;

	buf[i] = (unsigned char)(RD(adap, PSC_SMBTXRX) & 0xff);
	return 0;
}