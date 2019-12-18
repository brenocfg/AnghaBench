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
struct esas2r_adapter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_DEGRADED_MODE ; 
 int /*<<< orphan*/  ESAS2R_LOG_CRIT ; 
 int /*<<< orphan*/  esas2r_log (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool esas2r_set_degraded_mode(struct esas2r_adapter *a, char *error_str)
{
	set_bit(AF_DEGRADED_MODE, &a->flags);
	esas2r_log(ESAS2R_LOG_CRIT,
		   "setting adapter to degraded mode: %s\n", error_str);
	return false;
}