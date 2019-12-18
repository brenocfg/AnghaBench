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
struct net_device {int dummy; } ;
struct de_private {int ring_dma; struct net_device* dev; } ;
struct de_desc {int dummy; } ;

/* Variables and functions */
 int DE_RX_RING_SIZE ; 
 int /*<<< orphan*/  IntrMask ; 
 int /*<<< orphan*/  MacMode ; 
 int MacModeClear ; 
 int /*<<< orphan*/  RxMissed ; 
 int /*<<< orphan*/  RxRingAddr ; 
 int RxTx ; 
 int /*<<< orphan*/  TxRingAddr ; 
 int /*<<< orphan*/  de_adapter_wake (struct de_private*) ; 
 int de_intr_mask ; 
 int de_reset_mac (struct de_private*) ; 
 int /*<<< orphan*/  de_set_media (struct de_private*) ; 
 int /*<<< orphan*/  de_set_rx_mode (struct net_device*) ; 
 int dr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int de_init_hw (struct de_private *de)
{
	struct net_device *dev = de->dev;
	u32 macmode;
	int rc;

	de_adapter_wake(de);

	macmode = dr32(MacMode) & ~MacModeClear;

	rc = de_reset_mac(de);
	if (rc)
		return rc;

	de_set_media(de); /* reset phy */

	dw32(RxRingAddr, de->ring_dma);
	dw32(TxRingAddr, de->ring_dma + (sizeof(struct de_desc) * DE_RX_RING_SIZE));

	dw32(MacMode, RxTx | macmode);

	dr32(RxMissed); /* self-clearing */

	dw32(IntrMask, de_intr_mask);

	de_set_rx_mode(dev);

	return 0;
}