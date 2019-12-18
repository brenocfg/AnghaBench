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
struct ieee802154_hw {struct at86rf230_local* priv; } ;
struct at86rf230_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SR_AACK_DIS_ACK ; 
 int /*<<< orphan*/  SR_AACK_PROM_MODE ; 
 int at86rf230_write_subreg (struct at86rf230_local*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
at86rf230_set_promiscuous_mode(struct ieee802154_hw *hw, const bool on)
{
	struct at86rf230_local *lp = hw->priv;
	int rc;

	if (on) {
		rc = at86rf230_write_subreg(lp, SR_AACK_DIS_ACK, 1);
		if (rc < 0)
			return rc;

		rc = at86rf230_write_subreg(lp, SR_AACK_PROM_MODE, 1);
		if (rc < 0)
			return rc;
	} else {
		rc = at86rf230_write_subreg(lp, SR_AACK_PROM_MODE, 0);
		if (rc < 0)
			return rc;

		rc = at86rf230_write_subreg(lp, SR_AACK_DIS_ACK, 0);
		if (rc < 0)
			return rc;
	}

	return 0;
}