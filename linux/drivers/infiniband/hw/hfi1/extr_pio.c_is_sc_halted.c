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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  STATUS_CTXT_HALTED_SMASK ; 
 int read_kctxt_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool is_sc_halted(struct hfi1_devdata *dd, u32 hw_context)
{
	return !!(read_kctxt_csr(dd, hw_context, SC(STATUS)) &
		  SC(STATUS_CTXT_HALTED_SMASK));
}