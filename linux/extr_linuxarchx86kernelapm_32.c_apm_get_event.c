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
struct apm_bios_call {int err; scalar_t__ ecx; scalar_t__ ebx; int /*<<< orphan*/  func; } ;
typedef  scalar_t__ apm_eventinfo_t ;
typedef  scalar_t__ apm_event_t ;
struct TYPE_2__ {int connection_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  APM_FUNC_GET_EVENT ; 
 int APM_SUCCESS ; 
 scalar_t__ apm_bios_call (struct apm_bios_call*) ; 
 TYPE_1__ apm_info ; 

__attribute__((used)) static int apm_get_event(apm_event_t *event, apm_eventinfo_t *info)
{
	struct apm_bios_call call;

	call.func = APM_FUNC_GET_EVENT;
	call.ebx = call.ecx = 0;

	if (apm_bios_call(&call))
		return call.err;

	*event = call.ebx;
	if (apm_info.connection_version < 0x0102)
		*info = ~0; /* indicate info not valid */
	else
		*info = call.ecx;
	return APM_SUCCESS;
}