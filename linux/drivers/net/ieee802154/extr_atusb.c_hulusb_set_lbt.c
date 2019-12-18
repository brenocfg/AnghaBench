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
struct ieee802154_hw {struct atusb* priv; } ;
struct atusb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SR_CSMA_LBT_MODE ; 
 int atusb_write_subreg (struct atusb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
hulusb_set_lbt(struct ieee802154_hw *hw, bool on)
{
	struct atusb *atusb = hw->priv;

	return atusb_write_subreg(atusb, SR_CSMA_LBT_MODE, on);
}