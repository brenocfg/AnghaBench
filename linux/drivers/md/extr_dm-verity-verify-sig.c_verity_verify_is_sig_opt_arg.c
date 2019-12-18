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
 int /*<<< orphan*/  DM_VERITY_ROOT_HASH_VERIFICATION_OPT_SIG_KEY ; 
 int /*<<< orphan*/  strcasecmp (char const*,int /*<<< orphan*/ ) ; 

bool verity_verify_is_sig_opt_arg(const char *arg_name)
{
	return (!strcasecmp(arg_name,
			    DM_VERITY_ROOT_HASH_VERIFICATION_OPT_SIG_KEY));
}