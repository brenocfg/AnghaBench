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
struct hfi1_devdata {scalar_t__ vl15buf_cached; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSC_CM_RESET ; 
 scalar_t__ SEND_CM_CREDIT_VL ; 
 scalar_t__ SEND_CM_CREDIT_VL15 ; 
 scalar_t__ SEND_CM_GLOBAL_CREDIT ; 
 int TXE_NUM_DATA_VL ; 
 int /*<<< orphan*/  pio_send_control (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,scalar_t__,int /*<<< orphan*/ ) ; 

void reset_link_credits(struct hfi1_devdata *dd)
{
	int i;

	/* remove all previous VL credit limits */
	for (i = 0; i < TXE_NUM_DATA_VL; i++)
		write_csr(dd, SEND_CM_CREDIT_VL + (8 * i), 0);
	write_csr(dd, SEND_CM_CREDIT_VL15, 0);
	write_csr(dd, SEND_CM_GLOBAL_CREDIT, 0);
	/* reset the CM block */
	pio_send_control(dd, PSC_CM_RESET);
	/* reset cached value */
	dd->vl15buf_cached = 0;
}