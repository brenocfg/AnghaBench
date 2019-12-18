#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hfi1_ctxtdata {unsigned long ctxt; TYPE_1__* dd; } ;
struct TYPE_2__ {unsigned long first_dyn_alloc_ctxt; } ;

/* Variables and functions */
 unsigned long HFI1_MAX_SHARED_CTXTS ; 

__attribute__((used)) static inline unsigned long uctxt_offset(struct hfi1_ctxtdata *uctxt)
{
	return (uctxt->ctxt - uctxt->dd->first_dyn_alloc_ctxt) *
		HFI1_MAX_SHARED_CTXTS;
}