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
struct sdma_engine {int /*<<< orphan*/  err_progress_check_timer; int /*<<< orphan*/  this_idx; struct hfi1_devdata* dd; int /*<<< orphan*/  descq_head; int /*<<< orphan*/  progress_check_head; } ;
struct hfi1_devdata {unsigned int num_sdma; struct sdma_engine* per_sdma; } ;

/* Variables and functions */
 scalar_t__ HFI1_CAP_IS_KSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMA_AHG ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_bx (struct hfi1_devdata*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void sdma_err_progress_check_schedule(struct sdma_engine *sde)
{
	if (!is_bx(sde->dd) && HFI1_CAP_IS_KSET(SDMA_AHG)) {
		unsigned index;
		struct hfi1_devdata *dd = sde->dd;

		for (index = 0; index < dd->num_sdma; index++) {
			struct sdma_engine *curr_sdma = &dd->per_sdma[index];

			if (curr_sdma != sde)
				curr_sdma->progress_check_head =
							curr_sdma->descq_head;
		}
		dd_dev_err(sde->dd,
			   "SDMA engine %d - check scheduled\n",
				sde->this_idx);
		mod_timer(&sde->err_progress_check_timer, jiffies + 10);
	}
}