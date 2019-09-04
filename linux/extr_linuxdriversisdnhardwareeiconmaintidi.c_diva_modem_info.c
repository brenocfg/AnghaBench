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
struct TYPE_7__ {int* modem_parse_entry_first; int* modem_parse_entry_last; long modem_init_event; TYPE_1__* parse_table; } ;
typedef  TYPE_2__ diva_strace_context_t ;
typedef  int /*<<< orphan*/  diva_man_var_header_t ;
struct TYPE_6__ {int /*<<< orphan*/  variable; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIVA_SUPER_TRACE_NOTIFY_MODEM_CHANGE ; 
 int /*<<< orphan*/  diva_trace_error (TYPE_2__*,int,char*,int) ; 
 int /*<<< orphan*/  diva_trace_notify_user (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ diva_trace_read_variable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int diva_modem_info(diva_strace_context_t *pLib,
			   int Channel,
			   diva_man_var_header_t *pVar) {
	diva_man_var_header_t *cur;
	int i, nr = Channel - 1;

	for (i  = pLib->modem_parse_entry_first[nr];
	     i <= pLib->modem_parse_entry_last[nr]; i++) {
		if ((cur = find_var(pVar, pLib->parse_table[i].path))) {
			if (diva_trace_read_variable(cur, pLib->parse_table[i].variable)) {
				diva_trace_error(pLib, -3, __FILE__, __LINE__);
				return (-1);
			}
		} else {
			diva_trace_error(pLib, -2, __FILE__, __LINE__);
			return (-1);
		}
	}

	/*
	  We do not use first event to notify user - this is the event that is
	  generated as result of EVENT ON operation and is used only to initialize
	  internal variables of application
	*/
	if (pLib->modem_init_event & (1L << nr)) {
		diva_trace_notify_user(pLib, nr, DIVA_SUPER_TRACE_NOTIFY_MODEM_CHANGE);
	} else {
		pLib->modem_init_event |= (1L << nr);
	}

	return (0);
}