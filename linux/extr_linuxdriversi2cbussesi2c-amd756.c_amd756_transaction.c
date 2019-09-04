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
 int EIO ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int GE_ABORT ; 
 int GE_HOST_STC ; 
 int GS_CLEAR_STS ; 
 int GS_COL_STS ; 
 int GS_HCYC_STS ; 
 int GS_HST_STS ; 
 int GS_PRERR_STS ; 
 int GS_SMB_STS ; 
 int GS_TO_STS ; 
 int MAX_TIMEOUT ; 
 int /*<<< orphan*/  SMB_GLOBAL_ENABLE ; 
 int /*<<< orphan*/  SMB_GLOBAL_STATUS ; 
 int /*<<< orphan*/  SMB_HOST_ADDRESS ; 
 int /*<<< orphan*/  SMB_HOST_DATA ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  inb_p (int /*<<< orphan*/ ) ; 
 int inw (int /*<<< orphan*/ ) ; 
 int inw_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outw_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amd756_transaction(struct i2c_adapter *adap)
{
	int temp;
	int result = 0;
	int timeout = 0;

	dev_dbg(&adap->dev, "Transaction (pre): GS=%04x, GE=%04x, ADD=%04x, "
		"DAT=%04x\n", inw_p(SMB_GLOBAL_STATUS),
		inw_p(SMB_GLOBAL_ENABLE), inw_p(SMB_HOST_ADDRESS),
		inb_p(SMB_HOST_DATA));

	/* Make sure the SMBus host is ready to start transmitting */
	if ((temp = inw_p(SMB_GLOBAL_STATUS)) & (GS_HST_STS | GS_SMB_STS)) {
		dev_dbg(&adap->dev, "SMBus busy (%04x). Waiting...\n", temp);
		do {
			msleep(1);
			temp = inw_p(SMB_GLOBAL_STATUS);
		} while ((temp & (GS_HST_STS | GS_SMB_STS)) &&
		         (timeout++ < MAX_TIMEOUT));
		/* If the SMBus is still busy, we give up */
		if (timeout > MAX_TIMEOUT) {
			dev_dbg(&adap->dev, "Busy wait timeout (%04x)\n", temp);
			goto abort;
		}
		timeout = 0;
	}

	/* start the transaction by setting the start bit */
	outw_p(inw(SMB_GLOBAL_ENABLE) | GE_HOST_STC, SMB_GLOBAL_ENABLE);

	/* We will always wait for a fraction of a second! */
	do {
		msleep(1);
		temp = inw_p(SMB_GLOBAL_STATUS);
	} while ((temp & GS_HST_STS) && (timeout++ < MAX_TIMEOUT));

	/* If the SMBus is still busy, we give up */
	if (timeout > MAX_TIMEOUT) {
		dev_dbg(&adap->dev, "Completion timeout!\n");
		goto abort;
	}

	if (temp & GS_PRERR_STS) {
		result = -ENXIO;
		dev_dbg(&adap->dev, "SMBus Protocol error (no response)!\n");
	}

	if (temp & GS_COL_STS) {
		result = -EIO;
		dev_warn(&adap->dev, "SMBus collision!\n");
	}

	if (temp & GS_TO_STS) {
		result = -ETIMEDOUT;
		dev_dbg(&adap->dev, "SMBus protocol timeout!\n");
	}

	if (temp & GS_HCYC_STS)
		dev_dbg(&adap->dev, "SMBus protocol success!\n");

	outw_p(GS_CLEAR_STS, SMB_GLOBAL_STATUS);

#ifdef DEBUG
	if (((temp = inw_p(SMB_GLOBAL_STATUS)) & GS_CLEAR_STS) != 0x00) {
		dev_dbg(&adap->dev,
			"Failed reset at end of transaction (%04x)\n", temp);
	}
#endif

	dev_dbg(&adap->dev,
		"Transaction (post): GS=%04x, GE=%04x, ADD=%04x, DAT=%04x\n",
		inw_p(SMB_GLOBAL_STATUS), inw_p(SMB_GLOBAL_ENABLE),
		inw_p(SMB_HOST_ADDRESS), inb_p(SMB_HOST_DATA));

	return result;

 abort:
	dev_warn(&adap->dev, "Sending abort\n");
	outw_p(inw(SMB_GLOBAL_ENABLE) | GE_ABORT, SMB_GLOBAL_ENABLE);
	msleep(100);
	outw_p(GS_CLEAR_STS, SMB_GLOBAL_STATUS);
	return -EIO;
}