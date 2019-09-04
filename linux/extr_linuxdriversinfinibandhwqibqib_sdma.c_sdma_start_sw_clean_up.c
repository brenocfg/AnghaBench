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
struct qib_pportdata {int /*<<< orphan*/  sdma_sw_clean_up_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdma_start_sw_clean_up(struct qib_pportdata *ppd)
{
	tasklet_hi_schedule(&ppd->sdma_sw_clean_up_task);
}