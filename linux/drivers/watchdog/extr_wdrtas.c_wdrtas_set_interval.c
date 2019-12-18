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

/* Variables and functions */
 int /*<<< orphan*/  WDRTAS_SURVEILLANCE_IND ; 
 int /*<<< orphan*/  pr_err (char*,int,long) ; 
 long rtas_call (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wdrtas_token_set_indicator ; 

__attribute__((used)) static int wdrtas_set_interval(int interval)
{
	long result;
	static int print_msg = 10;

	/* rtas uses minutes */
	interval = (interval + 59) / 60;

	result = rtas_call(wdrtas_token_set_indicator, 3, 1, NULL,
			   WDRTAS_SURVEILLANCE_IND, 0, interval);
	if (result < 0 && print_msg) {
		pr_err("setting the watchdog to %i timeout failed: %li\n",
		       interval, result);
		print_msg--;
	}

	return result;
}