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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 scalar_t__ SEND_CM_CREDIT_VL ; 
 scalar_t__ SEND_CM_CREDIT_VL15 ; 
 int SEND_CM_CREDIT_VL_SHARED_LIMIT_VL_SHIFT ; 
 int SEND_CM_CREDIT_VL_SHARED_LIMIT_VL_SMASK ; 
 int TXE_NUM_DATA_VL ; 
 int read_csr (struct hfi1_devdata*,scalar_t__) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,scalar_t__,int) ; 

__attribute__((used)) static void set_vl_shared(struct hfi1_devdata *dd, int vl, u16 limit)
{
	u64 reg;
	u32 addr;

	if (vl < TXE_NUM_DATA_VL)
		addr = SEND_CM_CREDIT_VL + (8 * vl);
	else
		addr = SEND_CM_CREDIT_VL15;

	reg = read_csr(dd, addr);
	reg &= ~SEND_CM_CREDIT_VL_SHARED_LIMIT_VL_SMASK;
	reg |= (u64)limit << SEND_CM_CREDIT_VL_SHARED_LIMIT_VL_SHIFT;
	write_csr(dd, addr, reg);
}