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
typedef  int /*<<< orphan*/  u64 ;
struct hfi1_devdata {int /*<<< orphan*/ * gi_mask; } ;

/* Variables and functions */
 scalar_t__ CCE_INT_MAP ; 
 int CCE_NUM_INT_CSRS ; 
 int CCE_NUM_INT_MAP_CSRS ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,scalar_t__,int /*<<< orphan*/ ) ; 

void reset_interrupts(struct hfi1_devdata *dd)
{
	int i;

	/* all interrupts handled by the general handler */
	for (i = 0; i < CCE_NUM_INT_CSRS; i++)
		dd->gi_mask[i] = ~(u64)0;

	/* all chip interrupts map to MSI-X 0 */
	for (i = 0; i < CCE_NUM_INT_MAP_CSRS; i++)
		write_csr(dd, CCE_INT_MAP + (8 * i), 0);
}