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
struct TYPE_2__ {int /*<<< orphan*/  (* vcpu_kick ) (void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,int,void*) ; 
#define  XICS_RM_KICK_VCPU 128 
 TYPE_1__* kvmppc_host_rm_ops_hv ; 
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static void rm_host_ipi_action(int action, void *data)
{
	switch (action) {
	case XICS_RM_KICK_VCPU:
		kvmppc_host_rm_ops_hv->vcpu_kick(data);
		break;
	default:
		WARN(1, "Unexpected rm_action=%d data=%p\n", action, data);
		break;
	}

}