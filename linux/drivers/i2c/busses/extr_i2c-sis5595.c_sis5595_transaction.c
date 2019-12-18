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
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int MAX_TIMEOUT ; 
 int /*<<< orphan*/  SMB_CTL_LO ; 
 int /*<<< orphan*/  SMB_STS_HI ; 
 int /*<<< orphan*/  SMB_STS_LO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int sis5595_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sis5595_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sis5595_transaction(struct i2c_adapter *adap)
{
	int temp;
	int result = 0;
	int timeout = 0;

	/* Make sure the SMBus host is ready to start transmitting */
	temp = sis5595_read(SMB_STS_LO) + (sis5595_read(SMB_STS_HI) << 8);
	if (temp != 0x00) {
		dev_dbg(&adap->dev, "SMBus busy (%04x). Resetting...\n", temp);
		sis5595_write(SMB_STS_LO, temp & 0xff);
		sis5595_write(SMB_STS_HI, temp >> 8);
		if ((temp = sis5595_read(SMB_STS_LO) + (sis5595_read(SMB_STS_HI) << 8)) != 0x00) {
			dev_dbg(&adap->dev, "Failed! (%02x)\n", temp);
			return -EBUSY;
		} else {
			dev_dbg(&adap->dev, "Successful!\n");
		}
	}

	/* start the transaction by setting bit 4 */
	sis5595_write(SMB_CTL_LO, sis5595_read(SMB_CTL_LO) | 0x10);

	/* We will always wait for a fraction of a second! */
	do {
		msleep(1);
		temp = sis5595_read(SMB_STS_LO);
	} while (!(temp & 0x40) && (timeout++ < MAX_TIMEOUT));

	/* If the SMBus is still busy, we give up */
	if (timeout > MAX_TIMEOUT) {
		dev_dbg(&adap->dev, "SMBus Timeout!\n");
		result = -ETIMEDOUT;
	}

	if (temp & 0x10) {
		dev_dbg(&adap->dev, "Error: Failed bus transaction\n");
		result = -ENXIO;
	}

	if (temp & 0x20) {
		dev_err(&adap->dev, "Bus collision! SMBus may be locked until "
			"next hard reset (or not...)\n");
		/* Clock stops and slave is stuck in mid-transmission */
		result = -EIO;
	}

	temp = sis5595_read(SMB_STS_LO) + (sis5595_read(SMB_STS_HI) << 8);
	if (temp != 0x00) {
		sis5595_write(SMB_STS_LO, temp & 0xff);
		sis5595_write(SMB_STS_HI, temp >> 8);
	}

	temp = sis5595_read(SMB_STS_LO) + (sis5595_read(SMB_STS_HI) << 8);
	if (temp != 0x00)
		dev_dbg(&adap->dev, "Failed reset at end of transaction (%02x)\n", temp);

	return result;
}