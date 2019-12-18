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
typedef  int /*<<< orphan*/  uint32_t ;
struct timing_generator {int dummy; } ;

/* Variables and functions */

void optc1_set_early_control(
	struct timing_generator *optc,
	uint32_t early_cntl)
{
	/* asic design change, do not need this control
	 * empty for share caller logic
	 */
}