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
typedef  int u32 ;
struct timespec64 {int dummy; } ;
struct ptp_system_timestamp {int dummy; } ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {struct i40e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_PRTTSYN_TIME_H ; 
 int /*<<< orphan*/  I40E_PRTTSYN_TIME_L ; 
 struct timespec64 ns_to_timespec64 (int) ; 
 int /*<<< orphan*/  ptp_read_system_postts (struct ptp_system_timestamp*) ; 
 int /*<<< orphan*/  ptp_read_system_prets (struct ptp_system_timestamp*) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_ptp_read(struct i40e_pf *pf, struct timespec64 *ts,
			  struct ptp_system_timestamp *sts)
{
	struct i40e_hw *hw = &pf->hw;
	u32 hi, lo;
	u64 ns;

	/* The timer latches on the lowest register read. */
	ptp_read_system_prets(sts);
	lo = rd32(hw, I40E_PRTTSYN_TIME_L);
	ptp_read_system_postts(sts);
	hi = rd32(hw, I40E_PRTTSYN_TIME_H);

	ns = (((u64)hi) << 32) | lo;

	*ts = ns_to_timespec64(ns);
}