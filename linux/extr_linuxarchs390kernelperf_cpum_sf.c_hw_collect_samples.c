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
struct perf_event {int /*<<< orphan*/  hw; } ;
struct hws_trailer_entry {int /*<<< orphan*/  f; } ;
struct hws_basic_entry {int def; scalar_t__ I; scalar_t__ W; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAMPL_RATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_sample_entry (struct hws_basic_entry*,struct hws_trailer_entry*) ; 
 int /*<<< orphan*/  perf_event_count_update (struct perf_event*,int /*<<< orphan*/ ) ; 
 unsigned long long perf_push_sample (struct perf_event*,struct hws_basic_entry*) ; 
 scalar_t__ trailer_entry_ptr (unsigned long) ; 

__attribute__((used)) static void hw_collect_samples(struct perf_event *event, unsigned long *sdbt,
			       unsigned long long *overflow)
{
	struct hws_trailer_entry *te;
	struct hws_basic_entry *sample;

	te = (struct hws_trailer_entry *) trailer_entry_ptr(*sdbt);
	sample = (struct hws_basic_entry *) *sdbt;
	while ((unsigned long *) sample < (unsigned long *) te) {
		/* Check for an empty sample */
		if (!sample->def)
			break;

		/* Update perf event period */
		perf_event_count_update(event, SAMPL_RATE(&event->hw));

		/* Check whether sample is valid */
		if (sample->def == 0x0001) {
			/* If an event overflow occurred, the PMU is stopped to
			 * throttle event delivery.  Remaining sample data is
			 * discarded.
			 */
			if (!*overflow) {
				/* Check whether sample is consistent */
				if (sample->I == 0 && sample->W == 0) {
					/* Deliver sample data to perf */
					*overflow = perf_push_sample(event,
								     sample);
				}
			} else
				/* Count discarded samples */
				*overflow += 1;
		} else {
			debug_sample_entry(sample, te);
			/* Sample slot is not yet written or other record.
			 *
			 * This condition can occur if the buffer was reused
			 * from a combined basic- and diagnostic-sampling.
			 * If only basic-sampling is then active, entries are
			 * written into the larger diagnostic entries.
			 * This is typically the case for sample-data-blocks
			 * that are not full.  Stop processing if the first
			 * invalid format was detected.
			 */
			if (!te->f)
				break;
		}

		/* Reset sample slot and advance to next sample */
		sample->def = 0;
		sample++;
	}
}