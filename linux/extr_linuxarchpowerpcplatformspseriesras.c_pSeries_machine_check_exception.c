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
struct rtas_error_log {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 scalar_t__ fwnmi_active ; 
 struct rtas_error_log* fwnmi_get_errinfo (struct pt_regs*) ; 
 int /*<<< orphan*/  fwnmi_release_errinfo () ; 
 scalar_t__ recover_mce (struct pt_regs*,struct rtas_error_log*) ; 

int pSeries_machine_check_exception(struct pt_regs *regs)
{
	struct rtas_error_log *errp;

	if (fwnmi_active) {
		errp = fwnmi_get_errinfo(regs);
		fwnmi_release_errinfo();
		if (errp && recover_mce(regs, errp))
			return 1;
	}

	return 0;
}