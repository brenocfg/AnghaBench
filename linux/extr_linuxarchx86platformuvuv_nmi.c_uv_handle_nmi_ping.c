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
struct pt_regs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pinging; int /*<<< orphan*/  pings; int /*<<< orphan*/  queries; } ;

/* Variables and functions */
 int NMI_DONE ; 
 int /*<<< orphan*/  local64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ uv_cpu_nmi ; 
 int uv_handle_nmi (unsigned int,struct pt_regs*) ; 
 int /*<<< orphan*/  uv_nmi_ping_count ; 
 int /*<<< orphan*/  uv_nmi_ping_misses ; 

__attribute__((used)) static int uv_handle_nmi_ping(unsigned int reason, struct pt_regs *regs)
{
	int ret;

	this_cpu_inc(uv_cpu_nmi.queries);
	if (!this_cpu_read(uv_cpu_nmi.pinging)) {
		local64_inc(&uv_nmi_ping_misses);
		return NMI_DONE;
	}

	this_cpu_inc(uv_cpu_nmi.pings);
	local64_inc(&uv_nmi_ping_count);
	ret = uv_handle_nmi(reason, regs);
	this_cpu_write(uv_cpu_nmi.pinging, 0);
	return ret;
}