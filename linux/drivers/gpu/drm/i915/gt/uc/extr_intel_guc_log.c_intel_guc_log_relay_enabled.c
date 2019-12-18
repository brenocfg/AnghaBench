#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int buf_addr; } ;
struct intel_guc_log {TYPE_1__ relay; } ;

/* Variables and functions */

bool intel_guc_log_relay_enabled(const struct intel_guc_log *log)
{
	return log->relay.buf_addr;
}