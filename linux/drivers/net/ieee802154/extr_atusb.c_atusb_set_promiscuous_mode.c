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
 int /*<<< orphan*/  SR_AACK_DIS_ACK ; 
 int /*<<< orphan*/  SR_AACK_PROM_MODE ; 
 int atusb_write_subreg (struct atusb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
atusb_set_promiscuous_mode(struct ieee802154_hw *hw, const bool on)
{
	struct atusb *atusb = hw->priv;
	int ret;

	if (on) {
		ret = atusb_write_subreg(atusb, SR_AACK_DIS_ACK, 1);
		if (ret < 0)
			return ret;

		ret = atusb_write_subreg(atusb, SR_AACK_PROM_MODE, 1);
		if (ret < 0)
			return ret;
	} else {
		ret = atusb_write_subreg(atusb, SR_AACK_PROM_MODE, 0);
		if (ret < 0)
			return ret;

		ret = atusb_write_subreg(atusb, SR_AACK_DIS_ACK, 0);
		if (ret < 0)
			return ret;
	}

	return 0;
}