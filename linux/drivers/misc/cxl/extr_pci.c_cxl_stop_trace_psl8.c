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
struct cxl {int slices; int /*<<< orphan*/  afu_list_lock; scalar_t__* afu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL_SLICE_TRACE ; 
 int /*<<< orphan*/  CXL_PSL_TRACE ; 
 int /*<<< orphan*/  cxl_p1_write (struct cxl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cxl_p1n_write (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cxl_stop_trace_psl8(struct cxl *adapter)
{
	int slice;

	/* Stop the trace */
	cxl_p1_write(adapter, CXL_PSL_TRACE, 0x8000000000000017LL);

	/* Stop the slice traces */
	spin_lock(&adapter->afu_list_lock);
	for (slice = 0; slice < adapter->slices; slice++) {
		if (adapter->afu[slice])
			cxl_p1n_write(adapter->afu[slice], CXL_PSL_SLICE_TRACE,
				      0x8000000000000000LL);
	}
	spin_unlock(&adapter->afu_list_lock);
}