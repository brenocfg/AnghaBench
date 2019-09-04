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
struct seq_file {int dummy; } ;
struct TYPE_2__ {scalar_t__* deceased; scalar_t__* terminated; int /*<<< orphan*/  res_terminated_cnt; int /*<<< orphan*/  res_deceased_cnt; } ;

/* Variables and functions */
 int END_ATTEMPT ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 TYPE_1__* sm_state ; 
 int /*<<< orphan*/ * sm_stats_human_read ; 

__attribute__((used)) static int vc_sm_global_statistics_show(struct seq_file *s, void *v)
{
	int ix;

	/* Global state tracked statistics. */
	if (sm_state != NULL) {
		seq_puts(s, "\nDeceased Resources Statistics\n");

		seq_printf(s, "\nNatural Cause (%u occurences)\n",
			   sm_state->res_deceased_cnt);
		for (ix = 0; ix < END_ATTEMPT; ix++) {
			if (sm_state->deceased[ix] > 0) {
				seq_printf(s, "                %u\t%s\n",
					   sm_state->deceased[ix],
					   sm_stats_human_read[ix]);
			}
		}
		seq_puts(s, "\n");
		for (ix = 0; ix < END_ATTEMPT; ix++) {
			if (sm_state->deceased[ix + END_ATTEMPT] > 0) {
				seq_printf(s, "                %u\tFAILED %s\n",
					   sm_state->deceased[ix + END_ATTEMPT],
					   sm_stats_human_read[ix]);
			}
		}

		seq_printf(s, "\nForcefull (%u occurences)\n",
			   sm_state->res_terminated_cnt);
		for (ix = 0; ix < END_ATTEMPT; ix++) {
			if (sm_state->terminated[ix] > 0) {
				seq_printf(s, "                %u\t%s\n",
					   sm_state->terminated[ix],
					   sm_stats_human_read[ix]);
			}
		}
		seq_puts(s, "\n");
		for (ix = 0; ix < END_ATTEMPT; ix++) {
			if (sm_state->terminated[ix + END_ATTEMPT] > 0) {
				seq_printf(s, "                %u\tFAILED %s\n",
					   sm_state->terminated[ix +
								END_ATTEMPT],
					   sm_stats_human_read[ix]);
			}
		}
	}

	return 0;
}