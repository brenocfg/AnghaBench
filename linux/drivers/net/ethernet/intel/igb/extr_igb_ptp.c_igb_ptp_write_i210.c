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
typedef  int /*<<< orphan*/  u32 ;
struct timespec64 {scalar_t__ tv_sec; int /*<<< orphan*/  tv_nsec; } ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_SYSTIMH ; 
 int /*<<< orphan*/  E1000_SYSTIML ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igb_ptp_write_i210(struct igb_adapter *adapter,
			       const struct timespec64 *ts)
{
	struct e1000_hw *hw = &adapter->hw;

	/* Writing the SYSTIMR register is not necessary as it only provides
	 * sub-nanosecond resolution.
	 */
	wr32(E1000_SYSTIML, ts->tv_nsec);
	wr32(E1000_SYSTIMH, (u32)ts->tv_sec);
}