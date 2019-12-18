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
struct i2c_device {TYPE_1__ adapter; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SMBHSTCNT (struct i2c_device*) ; 
 int SMBHSTCNT_KILL ; 
 int /*<<< orphan*/  SMBHSTSTS (struct i2c_device*) ; 
 int SMBHSTSTS_BUS_ERR ; 
 int SMBHSTSTS_DEV_ERR ; 
 int SMBHSTSTS_FAILED ; 
 int SMBHSTSTS_HOST_BUSY ; 
 int STATUS_FLAGS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int i801_check_post(struct i2c_device *priv, int status, int timeout)
{
	int result = 0;

	/* If the SMBus is still busy, we give up */
	if (timeout) {
		dev_err(&priv->adapter.dev, "Transaction timeout\n");
		/* try to stop the current command */
		dev_dbg(&priv->adapter.dev, "Terminating the current operation\n");
		outb_p(inb_p(SMBHSTCNT(priv)) | SMBHSTCNT_KILL, SMBHSTCNT(priv));
		usleep_range(1000, 2000);
		outb_p(inb_p(SMBHSTCNT(priv)) & (~SMBHSTCNT_KILL), SMBHSTCNT(priv));

		/* Check if it worked */
		status = inb_p(SMBHSTSTS(priv));
		if ((status & SMBHSTSTS_HOST_BUSY) || !(status & SMBHSTSTS_FAILED))
			dev_err(&priv->adapter.dev, "Failed terminating the transaction\n");
		outb_p(STATUS_FLAGS, SMBHSTSTS(priv));
		return -ETIMEDOUT;
	}

	if (status & SMBHSTSTS_FAILED) {
		result = -EIO;
		dev_err(&priv->adapter.dev, "Transaction failed\n");
	}
	if (status & SMBHSTSTS_DEV_ERR) {
		result = -ENXIO;
		dev_dbg(&priv->adapter.dev, "No response\n");
	}
	if (status & SMBHSTSTS_BUS_ERR) {
		result = -EAGAIN;
		dev_dbg(&priv->adapter.dev, "Lost arbitration\n");
	}

	if (result) {
		/* Clear error flags */
		outb_p(status & STATUS_FLAGS, SMBHSTSTS(priv));
		status = inb_p(SMBHSTSTS(priv)) & STATUS_FLAGS;
		if (status)
			dev_warn(&priv->adapter.dev, "Failed clearing status flags at end of transaction (%02x)\n", status);
	}

	return result;
}