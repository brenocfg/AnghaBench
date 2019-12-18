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
struct rc_dev {struct ene_device* priv; } ;
struct ene_device {int transmitter_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  ene_tx_set_transmitters (struct ene_device*) ; 

__attribute__((used)) static int ene_set_tx_mask(struct rc_dev *rdev, u32 tx_mask)
{
	struct ene_device *dev = rdev->priv;
	dbg("TX: attempt to set transmitter mask %02x", tx_mask);

	/* invalid txmask */
	if (!tx_mask || tx_mask & ~0x03) {
		dbg("TX: invalid mask");
		/* return count of transmitters */
		return 2;
	}

	dev->transmitter_mask = tx_mask;
	ene_tx_set_transmitters(dev);
	return 0;
}