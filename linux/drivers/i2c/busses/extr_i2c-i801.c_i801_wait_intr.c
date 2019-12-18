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
struct i801_priv {TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int MAX_RETRIES ; 
 int /*<<< orphan*/  SMBHSTSTS (struct i801_priv*) ; 
 int SMBHSTSTS_HOST_BUSY ; 
 int SMBHSTSTS_INTR ; 
 int STATUS_ERROR_FLAGS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int i801_wait_intr(struct i801_priv *priv)
{
	int timeout = 0;
	int status;

	/* We will always wait for a fraction of a second! */
	do {
		usleep_range(250, 500);
		status = inb_p(SMBHSTSTS(priv));
	} while (((status & SMBHSTSTS_HOST_BUSY) ||
		  !(status & (STATUS_ERROR_FLAGS | SMBHSTSTS_INTR))) &&
		 (timeout++ < MAX_RETRIES));

	if (timeout > MAX_RETRIES) {
		dev_dbg(&priv->pci_dev->dev, "INTR Timeout!\n");
		return -ETIMEDOUT;
	}
	return status & (STATUS_ERROR_FLAGS | SMBHSTSTS_INTR);
}