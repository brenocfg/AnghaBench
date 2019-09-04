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
typedef  unsigned long long u64 ;
typedef  scalar_t__ u32 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 scalar_t__ CCE_INT_MASK ; 
 int CCE_NUM_INT_CSRS ; 
 unsigned long long get_int_mask (struct hfi1_devdata*,int) ; 
 int /*<<< orphan*/  init_qsfp_int (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,scalar_t__,unsigned long long) ; 

void set_intr_state(struct hfi1_devdata *dd, u32 enable)
{
	int i;

	/*
	 * In HFI, the mask needs to be 1 to allow interrupts.
	 */
	if (enable) {
		/* enable all interrupts but urgent on kernel contexts */
		for (i = 0; i < CCE_NUM_INT_CSRS; i++) {
			u64 mask = get_int_mask(dd, i);

			write_csr(dd, CCE_INT_MASK + (8 * i), mask);
		}

		init_qsfp_int(dd);
	} else {
		for (i = 0; i < CCE_NUM_INT_CSRS; i++)
			write_csr(dd, CCE_INT_MASK + (8 * i), 0ull);
	}
}