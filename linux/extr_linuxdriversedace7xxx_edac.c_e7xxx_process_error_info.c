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
struct mem_ctl_info {int dummy; } ;
struct e7xxx_error_info {int dram_ferr; int dram_nerr; } ;

/* Variables and functions */
 int /*<<< orphan*/  process_ce (struct mem_ctl_info*,struct e7xxx_error_info*) ; 
 int /*<<< orphan*/  process_ce_no_info (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  process_ue (struct mem_ctl_info*,struct e7xxx_error_info*) ; 
 int /*<<< orphan*/  process_ue_no_info (struct mem_ctl_info*) ; 

__attribute__((used)) static int e7xxx_process_error_info(struct mem_ctl_info *mci,
				struct e7xxx_error_info *info,
				int handle_errors)
{
	int error_found;

	error_found = 0;

	/* decode and report errors */
	if (info->dram_ferr & 1) {	/* check first error correctable */
		error_found = 1;

		if (handle_errors)
			process_ce(mci, info);
	}

	if (info->dram_ferr & 2) {	/* check first error uncorrectable */
		error_found = 1;

		if (handle_errors)
			process_ue(mci, info);
	}

	if (info->dram_nerr & 1) {	/* check next error correctable */
		error_found = 1;

		if (handle_errors) {
			if (info->dram_ferr & 1)
				process_ce_no_info(mci);
			else
				process_ce(mci, info);
		}
	}

	if (info->dram_nerr & 2) {	/* check next error uncorrectable */
		error_found = 1;

		if (handle_errors) {
			if (info->dram_ferr & 2)
				process_ue_no_info(mci);
			else
				process_ue(mci, info);
		}
	}

	return error_found;
}