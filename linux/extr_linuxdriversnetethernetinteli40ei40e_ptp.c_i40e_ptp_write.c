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
typedef  int u64 ;
struct timespec64 {int dummy; } ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {struct i40e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_PRTTSYN_TIME_H ; 
 int /*<<< orphan*/  I40E_PRTTSYN_TIME_L ; 
 int timespec64_to_ns (struct timespec64 const*) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void i40e_ptp_write(struct i40e_pf *pf, const struct timespec64 *ts)
{
	struct i40e_hw *hw = &pf->hw;
	u64 ns = timespec64_to_ns(ts);

	/* The timer will not update until the high register is written, so
	 * write the low register first.
	 */
	wr32(hw, I40E_PRTTSYN_TIME_L, ns & 0xFFFFFFFF);
	wr32(hw, I40E_PRTTSYN_TIME_H, ns >> 32);
}