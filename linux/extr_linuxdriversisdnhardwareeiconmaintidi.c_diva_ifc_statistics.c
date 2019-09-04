#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int statistic_parse_first; int statistic_parse_last; int mdm_statistic_parse_first; int mdm_statistic_parse_last; int fax_statistic_parse_first; int fax_statistic_parse_last; TYPE_1__* parse_table; } ;
typedef  TYPE_2__ diva_strace_context_t ;
typedef  int /*<<< orphan*/  diva_man_var_header_t ;
struct TYPE_6__ {int /*<<< orphan*/  variable; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIVA_SUPER_TRACE_NOTIFY_FAX_STAT_CHANGE ; 
 int /*<<< orphan*/  DIVA_SUPER_TRACE_NOTIFY_MDM_STAT_CHANGE ; 
 int /*<<< orphan*/  DIVA_SUPER_TRACE_NOTIFY_STAT_CHANGE ; 
 int /*<<< orphan*/  diva_trace_error (TYPE_2__*,int,char*,int) ; 
 int /*<<< orphan*/  diva_trace_notify_user (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ diva_trace_read_variable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int diva_ifc_statistics(diva_strace_context_t *pLib,
			       diva_man_var_header_t *pVar) {
	diva_man_var_header_t *cur;
	int i, one_updated = 0, mdm_updated = 0, fax_updated = 0;

	for (i  = pLib->statistic_parse_first; i <= pLib->statistic_parse_last; i++) {
		if ((cur = find_var(pVar, pLib->parse_table[i].path))) {
			if (diva_trace_read_variable(cur, pLib->parse_table[i].variable)) {
				diva_trace_error(pLib, -3 , __FILE__, __LINE__);
				return (-1);
			}
			one_updated = 1;
			if ((i >= pLib->mdm_statistic_parse_first) && (i <= pLib->mdm_statistic_parse_last)) {
				mdm_updated = 1;
			}
			if ((i >= pLib->fax_statistic_parse_first) && (i <= pLib->fax_statistic_parse_last)) {
				fax_updated = 1;
			}
		}
	}

	/*
	  We do not use first event to notify user - this is the event that is
	  generated as result of EVENT ON operation and is used only to initialize
	  internal variables of application
	*/
	if (mdm_updated) {
		diva_trace_notify_user(pLib, 0, DIVA_SUPER_TRACE_NOTIFY_MDM_STAT_CHANGE);
	} else if (fax_updated) {
		diva_trace_notify_user(pLib, 0, DIVA_SUPER_TRACE_NOTIFY_FAX_STAT_CHANGE);
	} else if (one_updated) {
		diva_trace_notify_user(pLib, 0, DIVA_SUPER_TRACE_NOTIFY_STAT_CHANGE);
	}

	return (one_updated ? 0 : -1);
}