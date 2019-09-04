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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {scalar_t__ cpu_start; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  FW_FEATURE_OPAL ; 
 long OPAL_SUCCESS ; 
 scalar_t__ OPAL_THREAD_INACTIVE ; 
 scalar_t__ OPAL_THREAD_STARTED ; 
 unsigned long __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  firmware_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_secondary_smp_init ; 
 unsigned int get_hard_smp_processor_id (int) ; 
 int nr_cpu_ids ; 
 long opal_query_cpu_status (unsigned int,scalar_t__*) ; 
 long opal_start_cpu (unsigned int,unsigned long) ; 
 TYPE_1__** paca_ptrs ; 
 int /*<<< orphan*/  ppc_function_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_devel (char*,int,unsigned int,...) ; 
 int /*<<< orphan*/  pr_warn (char*,long,int) ; 
 int smp_generic_kick_cpu (int) ; 

__attribute__((used)) static int pnv_smp_kick_cpu(int nr)
{
	unsigned int pcpu;
	unsigned long start_here =
			__pa(ppc_function_entry(generic_secondary_smp_init));
	long rc;
	uint8_t status;

	if (nr < 0 || nr >= nr_cpu_ids)
		return -EINVAL;

	pcpu = get_hard_smp_processor_id(nr);
	/*
	 * If we already started or OPAL is not supported, we just
	 * kick the CPU via the PACA
	 */
	if (paca_ptrs[nr]->cpu_start || !firmware_has_feature(FW_FEATURE_OPAL))
		goto kick;

	/*
	 * At this point, the CPU can either be spinning on the way in
	 * from kexec or be inside OPAL waiting to be started for the
	 * first time. OPAL v3 allows us to query OPAL to know if it
	 * has the CPUs, so we do that
	 */
	rc = opal_query_cpu_status(pcpu, &status);
	if (rc != OPAL_SUCCESS) {
		pr_warn("OPAL Error %ld querying CPU %d state\n", rc, nr);
		return -ENODEV;
	}

	/*
	 * Already started, just kick it, probably coming from
	 * kexec and spinning
	 */
	if (status == OPAL_THREAD_STARTED)
		goto kick;

	/*
	 * Available/inactive, let's kick it
	 */
	if (status == OPAL_THREAD_INACTIVE) {
		pr_devel("OPAL: Starting CPU %d (HW 0x%x)...\n", nr, pcpu);
		rc = opal_start_cpu(pcpu, start_here);
		if (rc != OPAL_SUCCESS) {
			pr_warn("OPAL Error %ld starting CPU %d\n", rc, nr);
			return -ENODEV;
		}
	} else {
		/*
		 * An unavailable CPU (or any other unknown status)
		 * shouldn't be started. It should also
		 * not be in the possible map but currently it can
		 * happen
		 */
		pr_devel("OPAL: CPU %d (HW 0x%x) is unavailable"
			 " (status %d)...\n", nr, pcpu, status);
		return -ENODEV;
	}

kick:
	return smp_generic_kick_cpu(nr);
}