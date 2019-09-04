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
 int EBUSY ; 
 int FEATURE_SMBUS_PEC ; 
 int /*<<< orphan*/  SMBAUXSTS (struct i801_priv*) ; 
 int SMBAUXSTS_CRCE ; 
 int /*<<< orphan*/  SMBHSTSTS (struct i801_priv*) ; 
 int SMBHSTSTS_HOST_BUSY ; 
 int STATUS_FLAGS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i801_check_pre(struct i801_priv *priv)
{
	int status;

	status = inb_p(SMBHSTSTS(priv));
	if (status & SMBHSTSTS_HOST_BUSY) {
		dev_err(&priv->pci_dev->dev, "SMBus is busy, can't use it!\n");
		return -EBUSY;
	}

	status &= STATUS_FLAGS;
	if (status) {
		dev_dbg(&priv->pci_dev->dev, "Clearing status flags (%02x)\n",
			status);
		outb_p(status, SMBHSTSTS(priv));
		status = inb_p(SMBHSTSTS(priv)) & STATUS_FLAGS;
		if (status) {
			dev_err(&priv->pci_dev->dev,
				"Failed clearing status flags (%02x)\n",
				status);
			return -EBUSY;
		}
	}

	/*
	 * Clear CRC status if needed.
	 * During normal operation, i801_check_post() takes care
	 * of it after every operation.  We do it here only in case
	 * the hardware was already in this state when the driver
	 * started.
	 */
	if (priv->features & FEATURE_SMBUS_PEC) {
		status = inb_p(SMBAUXSTS(priv)) & SMBAUXSTS_CRCE;
		if (status) {
			dev_dbg(&priv->pci_dev->dev,
				"Clearing aux status flags (%02x)\n", status);
			outb_p(status, SMBAUXSTS(priv));
			status = inb_p(SMBAUXSTS(priv)) & SMBAUXSTS_CRCE;
			if (status) {
				dev_err(&priv->pci_dev->dev,
					"Failed clearing aux status flags (%02x)\n",
					status);
				return -EBUSY;
			}
		}
	}

	return 0;
}