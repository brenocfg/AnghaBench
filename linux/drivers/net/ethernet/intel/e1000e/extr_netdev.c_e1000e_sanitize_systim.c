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
struct ptp_system_timestamp {int dummy; } ;
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int E1000_82574_SYSTIM_EPSILON ; 
 int E1000_MAX_82574_SYSTIM_REREADS ; 
 int E1000_TIMINCA_INCVALUE_MASK ; 
 int /*<<< orphan*/  SYSTIMH ; 
 int /*<<< orphan*/  SYSTIML ; 
 int /*<<< orphan*/  TIMINCA ; 
 int do_div (int,int) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptp_read_system_postts (struct ptp_system_timestamp*) ; 
 int /*<<< orphan*/  ptp_read_system_prets (struct ptp_system_timestamp*) ; 

__attribute__((used)) static u64 e1000e_sanitize_systim(struct e1000_hw *hw, u64 systim,
				  struct ptp_system_timestamp *sts)
{
	u64 time_delta, rem, temp;
	u64 systim_next;
	u32 incvalue;
	int i;

	incvalue = er32(TIMINCA) & E1000_TIMINCA_INCVALUE_MASK;
	for (i = 0; i < E1000_MAX_82574_SYSTIM_REREADS; i++) {
		/* latch SYSTIMH on read of SYSTIML */
		ptp_read_system_prets(sts);
		systim_next = (u64)er32(SYSTIML);
		ptp_read_system_postts(sts);
		systim_next |= (u64)er32(SYSTIMH) << 32;

		time_delta = systim_next - systim;
		temp = time_delta;
		/* VMWare users have seen incvalue of zero, don't div / 0 */
		rem = incvalue ? do_div(temp, incvalue) : (time_delta != 0);

		systim = systim_next;

		if ((time_delta < E1000_82574_SYSTIM_EPSILON) && (rem == 0))
			break;
	}

	return systim;
}