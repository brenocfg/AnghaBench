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
typedef  int u16 ;
struct i801_priv {int features; int status; int /*<<< orphan*/  waitq; int /*<<< orphan*/  pci_dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int FEATURE_HOST_NOTIFY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SMBHSTSTS (struct i801_priv*) ; 
 int SMBHSTSTS_BYTE_DONE ; 
 int SMBHSTSTS_INTR ; 
 int /*<<< orphan*/  SMBPCISTS ; 
 int SMBPCISTS_INTS ; 
 int /*<<< orphan*/  SMBSLVSTS (struct i801_priv*) ; 
 int SMBSLVSTS_HST_NTFY_STS ; 
 int STATUS_ERROR_FLAGS ; 
 int /*<<< orphan*/  i801_host_notify_isr (struct i801_priv*) ; 
 int /*<<< orphan*/  i801_isr_byte_done (struct i801_priv*) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t i801_isr(int irq, void *dev_id)
{
	struct i801_priv *priv = dev_id;
	u16 pcists;
	u8 status;

	/* Confirm this is our interrupt */
	pci_read_config_word(priv->pci_dev, SMBPCISTS, &pcists);
	if (!(pcists & SMBPCISTS_INTS))
		return IRQ_NONE;

	if (priv->features & FEATURE_HOST_NOTIFY) {
		status = inb_p(SMBSLVSTS(priv));
		if (status & SMBSLVSTS_HST_NTFY_STS)
			return i801_host_notify_isr(priv);
	}

	status = inb_p(SMBHSTSTS(priv));
	if (status & SMBHSTSTS_BYTE_DONE)
		i801_isr_byte_done(priv);

	/*
	 * Clear irq sources and report transaction result.
	 * ->status must be cleared before the next transaction is started.
	 */
	status &= SMBHSTSTS_INTR | STATUS_ERROR_FLAGS;
	if (status) {
		outb_p(status, SMBHSTSTS(priv));
		priv->status = status;
		wake_up(&priv->waitq);
	}

	return IRQ_HANDLED;
}