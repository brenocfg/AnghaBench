#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int MAX_TIMEOUT ; 
 int /*<<< orphan*/  SMB_CNT ; 
 int /*<<< orphan*/  SMB_HOST_CNT ; 
 int /*<<< orphan*/  SMB_STS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_1__ sis96x_adapter ; 
 int sis96x_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sis96x_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sis96x_transaction(int size)
{
	int temp;
	int result = 0;
	int timeout = 0;

	dev_dbg(&sis96x_adapter.dev, "SMBus transaction %d\n", size);

	/* Make sure the SMBus host is ready to start transmitting */
	if (((temp = sis96x_read(SMB_CNT)) & 0x03) != 0x00) {

		dev_dbg(&sis96x_adapter.dev, "SMBus busy (0x%02x). "
			"Resetting...\n", temp);

		/* kill the transaction */
		sis96x_write(SMB_HOST_CNT, 0x20);

		/* check it again */
		if (((temp = sis96x_read(SMB_CNT)) & 0x03) != 0x00) {
			dev_dbg(&sis96x_adapter.dev, "Failed (0x%02x)\n", temp);
			return -EBUSY;
		} else {
			dev_dbg(&sis96x_adapter.dev, "Successful\n");
		}
	}

	/* Turn off timeout interrupts, set fast host clock */
	sis96x_write(SMB_CNT, 0x20);

	/* clear all (sticky) status flags */
	temp = sis96x_read(SMB_STS);
	sis96x_write(SMB_STS, temp & 0x1e);

	/* start the transaction by setting bit 4 and size bits */
	sis96x_write(SMB_HOST_CNT, 0x10 | (size & 0x07));

	/* We will always wait for a fraction of a second! */
	do {
		msleep(1);
		temp = sis96x_read(SMB_STS);
	} while (!(temp & 0x0e) && (timeout++ < MAX_TIMEOUT));

	/* If the SMBus is still busy, we give up */
	if (timeout > MAX_TIMEOUT) {
		dev_dbg(&sis96x_adapter.dev, "SMBus Timeout! (0x%02x)\n", temp);
		result = -ETIMEDOUT;
	}

	/* device error - probably missing ACK */
	if (temp & 0x02) {
		dev_dbg(&sis96x_adapter.dev, "Failed bus transaction!\n");
		result = -ENXIO;
	}

	/* bus collision */
	if (temp & 0x04) {
		dev_dbg(&sis96x_adapter.dev, "Bus collision!\n");
		result = -EIO;
	}

	/* Finish up by resetting the bus */
	sis96x_write(SMB_STS, temp);
	if ((temp = sis96x_read(SMB_STS))) {
		dev_dbg(&sis96x_adapter.dev, "Failed reset at "
			"end of transaction! (0x%02x)\n", temp);
	}

	return result;
}