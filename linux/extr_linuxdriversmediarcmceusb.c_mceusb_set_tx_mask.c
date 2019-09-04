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
typedef  int u32 ;
struct rc_dev {struct mceusb_dev* priv; } ;
struct TYPE_2__ {scalar_t__ tx_mask_normal; } ;
struct mceusb_dev {int num_txports; int tx_mask; TYPE_1__ flags; } ;

/* Variables and functions */
 int MCE_DEFAULT_TX_MASK ; 

__attribute__((used)) static int mceusb_set_tx_mask(struct rc_dev *dev, u32 mask)
{
	struct mceusb_dev *ir = dev->priv;

	/* return number of transmitters */
	int emitters = ir->num_txports ? ir->num_txports : 2;

	if (mask >= (1 << emitters))
		return emitters;

	if (ir->flags.tx_mask_normal)
		ir->tx_mask = mask;
	else
		ir->tx_mask = (mask != MCE_DEFAULT_TX_MASK ?
				mask ^ MCE_DEFAULT_TX_MASK : mask) << 1;

	return 0;
}