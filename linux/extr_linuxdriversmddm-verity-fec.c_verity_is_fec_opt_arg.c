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
 int /*<<< orphan*/  DM_VERITY_OPT_FEC_BLOCKS ; 
 int /*<<< orphan*/  DM_VERITY_OPT_FEC_DEV ; 
 int /*<<< orphan*/  DM_VERITY_OPT_FEC_ROOTS ; 
 int /*<<< orphan*/  DM_VERITY_OPT_FEC_START ; 
 int /*<<< orphan*/  strcasecmp (char const*,int /*<<< orphan*/ ) ; 

bool verity_is_fec_opt_arg(const char *arg_name)
{
	return (!strcasecmp(arg_name, DM_VERITY_OPT_FEC_DEV) ||
		!strcasecmp(arg_name, DM_VERITY_OPT_FEC_BLOCKS) ||
		!strcasecmp(arg_name, DM_VERITY_OPT_FEC_START) ||
		!strcasecmp(arg_name, DM_VERITY_OPT_FEC_ROOTS));
}