#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  cpuid; } ;
struct TYPE_4__ {TYPE_1__ cpu_ol; } ;
struct xen_platform_op {TYPE_2__ u; int /*<<< orphan*/  interface_version; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int HYPERVISOR_platform_op (struct xen_platform_op*) ; 
 int /*<<< orphan*/  XENPF_INTERFACE_VERSION ; 
 int /*<<< orphan*/  XENPF_cpu_online ; 

__attribute__((used)) static int xen_pcpu_up(uint32_t cpu_id)
{
	struct xen_platform_op op = {
		.cmd			= XENPF_cpu_online,
		.interface_version	= XENPF_INTERFACE_VERSION,
		.u.cpu_ol.cpuid		= cpu_id,
	};

	return HYPERVISOR_platform_op(&op);
}