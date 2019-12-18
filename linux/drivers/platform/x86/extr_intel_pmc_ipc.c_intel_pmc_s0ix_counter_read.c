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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  has_gcr_regs; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  PMC_GCR_TELEM_DEEP_S0IX_REG ; 
 int /*<<< orphan*/  PMC_GCR_TELEM_SHLW_S0IX_REG ; 
 int /*<<< orphan*/  S0IX_RESIDENCY_IN_USECS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcr_data_readq (int /*<<< orphan*/ ) ; 
 TYPE_1__ ipcdev ; 

int intel_pmc_s0ix_counter_read(u64 *data)
{
	u64 deep, shlw;

	if (!ipcdev.has_gcr_regs)
		return -EACCES;

	deep = gcr_data_readq(PMC_GCR_TELEM_DEEP_S0IX_REG);
	shlw = gcr_data_readq(PMC_GCR_TELEM_SHLW_S0IX_REG);

	*data = S0IX_RESIDENCY_IN_USECS(deep, shlw);

	return 0;
}