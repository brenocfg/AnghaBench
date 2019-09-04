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
typedef  int u32 ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ALI1563_MAX_TIMEOUT ; 
 int EBUSY ; 
 int EIO ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int HST_CNTL1_TIMEOUT ; 
 int HST_CNTL2_KILL ; 
 int HST_CNTL2_QUICK ; 
 int HST_CNTL2_START ; 
 int HST_STS_BAD ; 
 int HST_STS_BUSERR ; 
 int HST_STS_BUSY ; 
 int HST_STS_DEVERR ; 
 int HST_STS_FAIL ; 
 int /*<<< orphan*/  SMB_HST_ADD ; 
 int /*<<< orphan*/  SMB_HST_CMD ; 
 int /*<<< orphan*/  SMB_HST_CNTL1 ; 
 int /*<<< orphan*/  SMB_HST_CNTL2 ; 
 int /*<<< orphan*/  SMB_HST_DAT0 ; 
 int /*<<< orphan*/  SMB_HST_DAT1 ; 
 int /*<<< orphan*/  SMB_HST_STS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ali1563_transaction(struct i2c_adapter *a, int size)
{
	u32 data;
	int timeout;
	int status = -EIO;

	dev_dbg(&a->dev, "Transaction (pre): STS=%02x, CNTL1=%02x, "
		"CNTL2=%02x, CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x\n",
		inb_p(SMB_HST_STS), inb_p(SMB_HST_CNTL1), inb_p(SMB_HST_CNTL2),
		inb_p(SMB_HST_CMD), inb_p(SMB_HST_ADD), inb_p(SMB_HST_DAT0),
		inb_p(SMB_HST_DAT1));

	data = inb_p(SMB_HST_STS);
	if (data & HST_STS_BAD) {
		dev_err(&a->dev, "ali1563: Trying to reset busy device\n");
		outb_p(data | HST_STS_BAD, SMB_HST_STS);
		data = inb_p(SMB_HST_STS);
		if (data & HST_STS_BAD)
			return -EBUSY;
	}
	outb_p(inb_p(SMB_HST_CNTL2) | HST_CNTL2_START, SMB_HST_CNTL2);

	timeout = ALI1563_MAX_TIMEOUT;
	do {
		msleep(1);
	} while (((data = inb_p(SMB_HST_STS)) & HST_STS_BUSY) && --timeout);

	dev_dbg(&a->dev, "Transaction (post): STS=%02x, CNTL1=%02x, "
		"CNTL2=%02x, CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x\n",
		inb_p(SMB_HST_STS), inb_p(SMB_HST_CNTL1), inb_p(SMB_HST_CNTL2),
		inb_p(SMB_HST_CMD), inb_p(SMB_HST_ADD), inb_p(SMB_HST_DAT0),
		inb_p(SMB_HST_DAT1));

	if (timeout && !(data & HST_STS_BAD))
		return 0;

	if (!timeout) {
		dev_err(&a->dev, "Timeout - Trying to KILL transaction!\n");
		/* Issue 'kill' to host controller */
		outb_p(HST_CNTL2_KILL, SMB_HST_CNTL2);
		data = inb_p(SMB_HST_STS);
		status = -ETIMEDOUT;
	}

	/* device error - no response, ignore the autodetection case */
	if (data & HST_STS_DEVERR) {
		if (size != HST_CNTL2_QUICK)
			dev_err(&a->dev, "Device error!\n");
		status = -ENXIO;
	}
	/* bus collision */
	if (data & HST_STS_BUSERR) {
		dev_err(&a->dev, "Bus collision!\n");
		/* Issue timeout, hoping it helps */
		outb_p(HST_CNTL1_TIMEOUT, SMB_HST_CNTL1);
	}

	if (data & HST_STS_FAIL) {
		dev_err(&a->dev, "Cleaning fail after KILL!\n");
		outb_p(0x0, SMB_HST_CNTL2);
	}

	return status;
}