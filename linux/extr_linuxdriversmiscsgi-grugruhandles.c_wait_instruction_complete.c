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
typedef  enum mcs_op { ____Placeholder_mcs_op } mcs_op ;

/* Variables and functions */
 int CCHSTATUS_ACTIVE ; 
 int GET_MSEG_HANDLE_STATUS (void*) ; 
 unsigned long GRU_OPERATION_TIMEOUT ; 
 int OPT_STATS ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long get_cycles () ; 
 int gru_options ; 
 int /*<<< orphan*/  report_instruction_timeout (void*) ; 
 int /*<<< orphan*/  update_mcs_stats (int,unsigned long) ; 

__attribute__((used)) static int wait_instruction_complete(void *h, enum mcs_op opc)
{
	int status;
	unsigned long start_time = get_cycles();

	while (1) {
		cpu_relax();
		status = GET_MSEG_HANDLE_STATUS(h);
		if (status != CCHSTATUS_ACTIVE)
			break;
		if (GRU_OPERATION_TIMEOUT < (get_cycles() - start_time)) {
			report_instruction_timeout(h);
			start_time = get_cycles();
		}
	}
	if (gru_options & OPT_STATS)
		update_mcs_stats(opc, get_cycles() - start_time);
	return status;
}