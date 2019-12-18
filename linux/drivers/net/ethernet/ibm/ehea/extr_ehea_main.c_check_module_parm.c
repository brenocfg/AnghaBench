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
 scalar_t__ EHEA_MAX_ENTRIES_RQ1 ; 
 scalar_t__ EHEA_MAX_ENTRIES_RQ2 ; 
 scalar_t__ EHEA_MAX_ENTRIES_RQ3 ; 
 scalar_t__ EHEA_MAX_ENTRIES_SQ ; 
 scalar_t__ EHEA_MIN_ENTRIES_QP ; 
 int EINVAL ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ rq1_entries ; 
 scalar_t__ rq2_entries ; 
 scalar_t__ rq3_entries ; 
 scalar_t__ sq_entries ; 

__attribute__((used)) static int check_module_parm(void)
{
	int ret = 0;

	if ((rq1_entries < EHEA_MIN_ENTRIES_QP) ||
	    (rq1_entries > EHEA_MAX_ENTRIES_RQ1)) {
		pr_info("Bad parameter: rq1_entries\n");
		ret = -EINVAL;
	}
	if ((rq2_entries < EHEA_MIN_ENTRIES_QP) ||
	    (rq2_entries > EHEA_MAX_ENTRIES_RQ2)) {
		pr_info("Bad parameter: rq2_entries\n");
		ret = -EINVAL;
	}
	if ((rq3_entries < EHEA_MIN_ENTRIES_QP) ||
	    (rq3_entries > EHEA_MAX_ENTRIES_RQ3)) {
		pr_info("Bad parameter: rq3_entries\n");
		ret = -EINVAL;
	}
	if ((sq_entries < EHEA_MIN_ENTRIES_QP) ||
	    (sq_entries > EHEA_MAX_ENTRIES_SQ)) {
		pr_info("Bad parameter: sq_entries\n");
		ret = -EINVAL;
	}

	return ret;
}