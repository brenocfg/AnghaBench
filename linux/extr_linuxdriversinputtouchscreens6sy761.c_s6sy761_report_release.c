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
typedef  int /*<<< orphan*/  u8 ;
struct s6sy761_data {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_TOOL_FINGER ; 
 int /*<<< orphan*/  input_mt_report_slot_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_mt_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s6sy761_report_release(struct s6sy761_data *sdata,
				   u8 *event, u8 tid)
{
	input_mt_slot(sdata->input, tid);
	input_mt_report_slot_state(sdata->input, MT_TOOL_FINGER, false);

	input_sync(sdata->input);
}