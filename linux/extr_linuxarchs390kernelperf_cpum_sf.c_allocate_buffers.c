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
struct hws_basic_entry {int dummy; } ;
struct hw_perf_event {int dummy; } ;
struct cpu_hw_sf {int /*<<< orphan*/  sfb; int /*<<< orphan*/  qsi; } ;

/* Variables and functions */
 unsigned long CPUM_SF_MIN_SDB ; 
 unsigned long DIV_ROUND_UP (unsigned long,unsigned long) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SAMPL_RATE (struct hw_perf_event*) ; 
 int alloc_sampling_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_sprintf_event (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ ,size_t,struct cpu_hw_sf*) ; 
 unsigned long sample_rate_to_freq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sf_buffer_available (struct cpu_hw_sf*) ; 
 int /*<<< orphan*/  sfb_init_allocs (unsigned long,struct hw_perf_event*) ; 
 int /*<<< orphan*/  sfb_max_limit (struct hw_perf_event*) ; 
 int /*<<< orphan*/  sfb_pending_allocs (int /*<<< orphan*/ *,struct hw_perf_event*) ; 
 int /*<<< orphan*/  sfdbg ; 

__attribute__((used)) static int allocate_buffers(struct cpu_hw_sf *cpuhw, struct hw_perf_event *hwc)
{
	unsigned long n_sdb, freq, factor;
	size_t sample_size;

	/* Calculate sampling buffers using 4K pages
	 *
	 *    1. Determine the sample data size which depends on the used
	 *	 sampling functions, for example, basic-sampling or
	 *	 basic-sampling with diagnostic-sampling.
	 *
	 *    2. Use the sampling frequency as input.  The sampling buffer is
	 *	 designed for almost one second.  This can be adjusted through
	 *	 the "factor" variable.
	 *	 In any case, alloc_sampling_buffer() sets the Alert Request
	 *	 Control indicator to trigger a measurement-alert to harvest
	 *	 sample-data-blocks (sdb).
	 *
	 *    3. Compute the number of sample-data-blocks and ensure a minimum
	 *	 of CPUM_SF_MIN_SDB.  Also ensure the upper limit does not
	 *	 exceed a "calculated" maximum.  The symbolic maximum is
	 *	 designed for basic-sampling only and needs to be increased if
	 *	 diagnostic-sampling is active.
	 *	 See also the remarks for these symbolic constants.
	 *
	 *    4. Compute the number of sample-data-block-tables (SDBT) and
	 *	 ensure a minimum of CPUM_SF_MIN_SDBT (one table can manage up
	 *	 to 511 SDBs).
	 */
	sample_size = sizeof(struct hws_basic_entry);
	freq = sample_rate_to_freq(&cpuhw->qsi, SAMPL_RATE(hwc));
	factor = 1;
	n_sdb = DIV_ROUND_UP(freq, factor * ((PAGE_SIZE-64) / sample_size));
	if (n_sdb < CPUM_SF_MIN_SDB)
		n_sdb = CPUM_SF_MIN_SDB;

	/* If there is already a sampling buffer allocated, it is very likely
	 * that the sampling facility is enabled too.  If the event to be
	 * initialized requires a greater sampling buffer, the allocation must
	 * be postponed.  Changing the sampling buffer requires the sampling
	 * facility to be in the disabled state.  So, account the number of
	 * required SDBs and let cpumsf_pmu_enable() resize the buffer just
	 * before the event is started.
	 */
	sfb_init_allocs(n_sdb, hwc);
	if (sf_buffer_available(cpuhw))
		return 0;

	debug_sprintf_event(sfdbg, 3,
			    "allocate_buffers: rate=%lu f=%lu sdb=%lu/%lu"
			    " sample_size=%lu cpuhw=%p\n",
			    SAMPL_RATE(hwc), freq, n_sdb, sfb_max_limit(hwc),
			    sample_size, cpuhw);

	return alloc_sampling_buffer(&cpuhw->sfb,
				     sfb_pending_allocs(&cpuhw->sfb, hwc));
}