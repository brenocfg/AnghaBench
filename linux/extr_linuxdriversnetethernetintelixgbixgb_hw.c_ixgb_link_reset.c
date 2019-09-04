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
typedef  scalar_t__ u8 ;
struct ixgb_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL0 ; 
 int IXGB_CTRL0_LRST ; 
 int /*<<< orphan*/  IXGB_DELAY_USECS_AFTER_LINK_RESET ; 
 int IXGB_READ_REG (struct ixgb_hw*,int /*<<< orphan*/ ) ; 
 int IXGB_STATUS_LU ; 
 int /*<<< orphan*/  IXGB_WRITE_REG (struct ixgb_hw*,int /*<<< orphan*/ ,int) ; 
 int IXGB_XPCSS_ALIGN_STATUS ; 
 scalar_t__ MAX_RESET_ITERATIONS ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  XPCSS ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ixgb_link_reset(struct ixgb_hw *hw)
{
	bool link_status = false;
	u8 wait_retries = MAX_RESET_ITERATIONS;
	u8 lrst_retries = MAX_RESET_ITERATIONS;

	do {
		/* Reset the link */
		IXGB_WRITE_REG(hw, CTRL0,
			       IXGB_READ_REG(hw, CTRL0) | IXGB_CTRL0_LRST);

		/* Wait for link-up and lane re-alignment */
		do {
			udelay(IXGB_DELAY_USECS_AFTER_LINK_RESET);
			link_status =
			    ((IXGB_READ_REG(hw, STATUS) & IXGB_STATUS_LU)
			     && (IXGB_READ_REG(hw, XPCSS) &
				 IXGB_XPCSS_ALIGN_STATUS)) ? true : false;
		} while (!link_status && --wait_retries);

	} while (!link_status && --lrst_retries);

	return link_status;
}