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
struct link_config {int supported; int requested_fc; int fc; int advertising; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  requested_duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  requested_speed; } ;
struct board_info {int caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_INVALID ; 
 int PAUSE_AUTONEG ; 
 int PAUSE_RX ; 
 int PAUSE_TX ; 
 int /*<<< orphan*/  SPEED_INVALID ; 
 int SUPPORTED_Autoneg ; 

__attribute__((used)) static void init_link_config(struct link_config *lc,
			     const struct board_info *bi)
{
	lc->supported = bi->caps;
	lc->requested_speed = lc->speed = SPEED_INVALID;
	lc->requested_duplex = lc->duplex = DUPLEX_INVALID;
	lc->requested_fc = lc->fc = PAUSE_RX | PAUSE_TX;
	if (lc->supported & SUPPORTED_Autoneg) {
		lc->advertising = lc->supported;
		lc->autoneg = AUTONEG_ENABLE;
		lc->requested_fc |= PAUSE_AUTONEG;
	} else {
		lc->advertising = 0;
		lc->autoneg = AUTONEG_DISABLE;
	}
}