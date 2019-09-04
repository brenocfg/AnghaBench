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
struct sii9234 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MHL_TX_DISC_CTRL1_REG ; 
 int /*<<< orphan*/  MHL_TX_DISC_CTRL3_REG ; 
 int /*<<< orphan*/  MHL_TX_DISC_CTRL6_REG ; 
 int /*<<< orphan*/  MHL_TX_INT_CTRL_REG ; 
 int USB_ID_OVR ; 
 int /*<<< orphan*/  mhl_tx_writebm (struct sii9234*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void force_usb_id_switch_open(struct sii9234 *ctx)
{
	/* Disable CBUS discovery */
	mhl_tx_writebm(ctx, MHL_TX_DISC_CTRL1_REG, 0, 0x01);
	/* Force USB ID switch to open */
	mhl_tx_writebm(ctx, MHL_TX_DISC_CTRL6_REG, ~0, USB_ID_OVR);
	mhl_tx_writebm(ctx, MHL_TX_DISC_CTRL3_REG, ~0, 0x86);
	/* Force upstream HPD to 0 when not in MHL mode. */
	mhl_tx_writebm(ctx, MHL_TX_INT_CTRL_REG, 0, 0x30);
}