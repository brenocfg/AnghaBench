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
struct q6v5 {int /*<<< orphan*/  mss_restart; int /*<<< orphan*/  pdc_reset; scalar_t__ has_alt_reset; } ;

/* Variables and functions */
 int reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int reset_control_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int q6v5_reset_assert(struct q6v5 *qproc)
{
	int ret;

	if (qproc->has_alt_reset) {
		reset_control_assert(qproc->pdc_reset);
		ret = reset_control_reset(qproc->mss_restart);
		reset_control_deassert(qproc->pdc_reset);
	} else {
		ret = reset_control_assert(qproc->mss_restart);
	}

	return ret;
}