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
struct cyttsp4_mt_data {scalar_t__ num_prv_tch; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int /*<<< orphan*/  input_mt_report_slot_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cyttsp4_report_slot_liftoff(struct cyttsp4_mt_data *md,
		int max_slots)
{
	int t;

	if (md->num_prv_tch == 0)
		return;

	for (t = 0; t < max_slots; t++) {
		input_mt_slot(md->input, t);
		input_mt_report_slot_state(md->input,
			MT_TOOL_FINGER, false);
	}
}