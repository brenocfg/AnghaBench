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
struct pseries_errorlog {scalar_t__ data; } ;
struct epow_errorlog {int sensor_value; int event_modifier; } ;

/* Variables and functions */
#define  EPOW_MAIN_ENCLOSURE 134 
#define  EPOW_POWER_OFF 133 
#define  EPOW_RESET 132 
#define  EPOW_SYSTEM_HALT 131 
#define  EPOW_SYSTEM_SHUTDOWN 130 
#define  EPOW_WARN_COOLING 129 
#define  EPOW_WARN_POWER 128 
 int /*<<< orphan*/  PSERIES_ELOG_SECT_ID_EPOW ; 
 int /*<<< orphan*/  emergency_sync () ; 
 struct pseries_errorlog* get_pseries_errorlog (struct rtas_error_log*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_system_shutdown (int) ; 
 int /*<<< orphan*/  kernel_power_off () ; 
 scalar_t__ num_epow_events ; 
 int /*<<< orphan*/  orderly_poweroff (int) ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 
 int /*<<< orphan*/  pr_err (char*,char) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void rtas_parse_epow_errlog(struct rtas_error_log *log)
{
	struct pseries_errorlog *pseries_log;
	struct epow_errorlog *epow_log;
	char action_code;
	char modifier;

	pseries_log = get_pseries_errorlog(log, PSERIES_ELOG_SECT_ID_EPOW);
	if (pseries_log == NULL)
		return;

	epow_log = (struct epow_errorlog *)pseries_log->data;
	action_code = epow_log->sensor_value & 0xF;	/* bottom 4 bits */
	modifier = epow_log->event_modifier & 0xF;	/* bottom 4 bits */

	switch (action_code) {
	case EPOW_RESET:
		if (num_epow_events) {
			pr_info("Non critical power/cooling issue cleared\n");
			num_epow_events--;
		}
		break;

	case EPOW_WARN_COOLING:
		pr_info("Non-critical cooling issue detected. Check RTAS error"
			" log for details\n");
		break;

	case EPOW_WARN_POWER:
		pr_info("Non-critical power issue detected. Check RTAS error"
			" log for details\n");
		break;

	case EPOW_SYSTEM_SHUTDOWN:
		handle_system_shutdown(epow_log->event_modifier);
		break;

	case EPOW_SYSTEM_HALT:
		pr_emerg("Critical power/cooling issue detected. Check RTAS"
			 " error log for details. Powering off.\n");
		orderly_poweroff(true);
		break;

	case EPOW_MAIN_ENCLOSURE:
	case EPOW_POWER_OFF:
		pr_emerg("System about to lose power. Check RTAS error log "
			 " for details. Powering off immediately.\n");
		emergency_sync();
		kernel_power_off();
		break;

	default:
		pr_err("Unknown power/cooling event (action code  = %d)\n",
			action_code);
	}

	/* Increment epow events counter variable */
	if (action_code != EPOW_RESET)
		num_epow_events++;
}