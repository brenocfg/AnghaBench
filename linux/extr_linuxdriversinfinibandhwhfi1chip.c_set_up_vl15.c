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
typedef  scalar_t__ u16 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_CM_CREDIT_VL15 ; 
 int SEND_CM_CREDIT_VL15_DEDICATED_LIMIT_VL_SHIFT ; 
 int /*<<< orphan*/  SEND_CM_GLOBAL_CREDIT ; 
 int SEND_CM_GLOBAL_CREDIT_SHARED_LIMIT_SMASK ; 
 int SEND_CM_GLOBAL_CREDIT_TOTAL_CREDIT_LIMIT_SHIFT ; 
 int SEND_CM_GLOBAL_CREDIT_TOTAL_CREDIT_LIMIT_SMASK ; 
 int read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int) ; 

void set_up_vl15(struct hfi1_devdata *dd, u16 vl15buf)
{
	u64 reg = read_csr(dd, SEND_CM_GLOBAL_CREDIT);

	/* set initial values for total and shared credit limit */
	reg &= ~(SEND_CM_GLOBAL_CREDIT_TOTAL_CREDIT_LIMIT_SMASK |
		 SEND_CM_GLOBAL_CREDIT_SHARED_LIMIT_SMASK);

	/*
	 * Set total limit to be equal to VL15 credits.
	 * Leave shared limit at 0.
	 */
	reg |= (u64)vl15buf << SEND_CM_GLOBAL_CREDIT_TOTAL_CREDIT_LIMIT_SHIFT;
	write_csr(dd, SEND_CM_GLOBAL_CREDIT, reg);

	write_csr(dd, SEND_CM_CREDIT_VL15, (u64)vl15buf
		  << SEND_CM_CREDIT_VL15_DEDICATED_LIMIT_VL_SHIFT);
}