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
struct i801_priv {int features; TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBADMSG ; 
 int EIO ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int FEATURE_SMBUS_PEC ; 
 int /*<<< orphan*/  SMBAUXSTS (struct i801_priv*) ; 
 int SMBAUXSTS_CRCE ; 
 int /*<<< orphan*/  SMBHSTCNT (struct i801_priv*) ; 
 int SMBHSTCNT_KILL ; 
 int /*<<< orphan*/  SMBHSTSTS (struct i801_priv*) ; 
 int SMBHSTSTS_BUS_ERR ; 
 int SMBHSTSTS_DEV_ERR ; 
 int SMBHSTSTS_FAILED ; 
 int SMBHSTSTS_HOST_BUSY ; 
 int STATUS_FLAGS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int i801_check_post(struct i801_priv *priv, int status)
{
	int result = 0;

	/*
	 * If the SMBus is still busy, we give up
	 * Note: This timeout condition only happens when using polling
	 * transactions.  For interrupt operation, NAK/timeout is indicated by
	 * DEV_ERR.
	 */
	if (unlikely(status < 0)) {
		dev_err(&priv->pci_dev->dev, "Transaction timeout\n");
		/* try to stop the current command */
		dev_dbg(&priv->pci_dev->dev, "Terminating the current operation\n");
		outb_p(inb_p(SMBHSTCNT(priv)) | SMBHSTCNT_KILL,
		       SMBHSTCNT(priv));
		usleep_range(1000, 2000);
		outb_p(inb_p(SMBHSTCNT(priv)) & (~SMBHSTCNT_KILL),
		       SMBHSTCNT(priv));

		/* Check if it worked */
		status = inb_p(SMBHSTSTS(priv));
		if ((status & SMBHSTSTS_HOST_BUSY) ||
		    !(status & SMBHSTSTS_FAILED))
			dev_err(&priv->pci_dev->dev,
				"Failed terminating the transaction\n");
		outb_p(STATUS_FLAGS, SMBHSTSTS(priv));
		return -ETIMEDOUT;
	}

	if (status & SMBHSTSTS_FAILED) {
		result = -EIO;
		dev_err(&priv->pci_dev->dev, "Transaction failed\n");
	}
	if (status & SMBHSTSTS_DEV_ERR) {
		/*
		 * This may be a PEC error, check and clear it.
		 *
		 * AUXSTS is handled differently from HSTSTS.
		 * For HSTSTS, i801_isr() or i801_wait_intr()
		 * has already cleared the error bits in hardware,
		 * and we are passed a copy of the original value
		 * in "status".
		 * For AUXSTS, the hardware register is left
		 * for us to handle here.
		 * This is asymmetric, slightly iffy, but safe,
		 * since all this code is serialized and the CRCE
		 * bit is harmless as long as it's cleared before
		 * the next operation.
		 */
		if ((priv->features & FEATURE_SMBUS_PEC) &&
		    (inb_p(SMBAUXSTS(priv)) & SMBAUXSTS_CRCE)) {
			outb_p(SMBAUXSTS_CRCE, SMBAUXSTS(priv));
			result = -EBADMSG;
			dev_dbg(&priv->pci_dev->dev, "PEC error\n");
		} else {
			result = -ENXIO;
			dev_dbg(&priv->pci_dev->dev, "No response\n");
		}
	}
	if (status & SMBHSTSTS_BUS_ERR) {
		result = -EAGAIN;
		dev_dbg(&priv->pci_dev->dev, "Lost arbitration\n");
	}

	/* Clear status flags except BYTE_DONE, to be cleared by caller */
	outb_p(status, SMBHSTSTS(priv));

	return result;
}