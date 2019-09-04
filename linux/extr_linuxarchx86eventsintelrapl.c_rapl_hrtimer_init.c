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
struct hrtimer {int /*<<< orphan*/  function; } ;
struct rapl_pmu {struct hrtimer hrtimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  hrtimer_init (struct hrtimer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rapl_hrtimer_handle ; 

__attribute__((used)) static void rapl_hrtimer_init(struct rapl_pmu *pmu)
{
	struct hrtimer *hr = &pmu->hrtimer;

	hrtimer_init(hr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	hr->function = rapl_hrtimer_handle;
}