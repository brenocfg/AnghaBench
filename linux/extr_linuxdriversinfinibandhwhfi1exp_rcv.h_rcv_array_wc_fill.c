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
typedef  int u32 ;
struct hfi1_devdata {int flags; scalar_t__ rcvarray_wc; } ;

/* Variables and functions */
 int HFI1_PRESENT ; 
 int /*<<< orphan*/  flush_wc () ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void rcv_array_wc_fill(struct hfi1_devdata *dd, u32 index)
{
	/*
	 * Doing the WC fill writes only makes sense if the device is
	 * present and the RcvArray has been mapped as WC memory.
	 */
	if ((dd->flags & HFI1_PRESENT) && dd->rcvarray_wc) {
		writeq(0, dd->rcvarray_wc + (index * 8));
		if ((index & 3) == 3)
			flush_wc();
	}
}