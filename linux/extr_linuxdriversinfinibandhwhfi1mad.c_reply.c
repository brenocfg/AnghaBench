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
struct ib_mad_hdr {scalar_t__ mgmt_class; int /*<<< orphan*/  status; int /*<<< orphan*/  method; } ;

/* Variables and functions */
 int IB_MAD_RESULT_REPLY ; 
 int IB_MAD_RESULT_SUCCESS ; 
 scalar_t__ IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE ; 
 int /*<<< orphan*/  IB_MGMT_METHOD_GET_RESP ; 
 int /*<<< orphan*/  IB_SMP_DIRECTION ; 

__attribute__((used)) static int reply(struct ib_mad_hdr *smp)
{
	/*
	 * The verbs framework will handle the directed/LID route
	 * packet changes.
	 */
	smp->method = IB_MGMT_METHOD_GET_RESP;
	if (smp->mgmt_class == IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE)
		smp->status |= IB_SMP_DIRECTION;
	return IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_REPLY;
}