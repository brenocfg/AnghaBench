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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct kvmppc_xics {int dummy; } ;
struct kvmppc_ics {struct ics_irq_state* irq_state; } ;
struct kvmppc_icp {int dummy; } ;
struct TYPE_2__ {struct kvmppc_xics* xics; } ;
struct kvm {TYPE_1__ arch; } ;
struct ics_irq_state {int /*<<< orphan*/  resend; int /*<<< orphan*/  masked_pending; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  XICS_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icp_deliver_irq (struct kvmppc_xics*,struct kvmppc_icp*,int /*<<< orphan*/ ,int) ; 
 struct kvmppc_ics* kvmppc_xics_find_ics (struct kvmppc_xics*,int /*<<< orphan*/ ,size_t*) ; 
 struct kvmppc_icp* kvmppc_xics_find_server (struct kvm*,int /*<<< orphan*/ ) ; 
 scalar_t__ write_xive (struct kvmppc_xics*,struct kvmppc_ics*,struct ics_irq_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int kvmppc_xics_set_xive(struct kvm *kvm, u32 irq, u32 server, u32 priority)
{
	struct kvmppc_xics *xics = kvm->arch.xics;
	struct kvmppc_icp *icp;
	struct kvmppc_ics *ics;
	struct ics_irq_state *state;
	u16 src;

	if (!xics)
		return -ENODEV;

	ics = kvmppc_xics_find_ics(xics, irq, &src);
	if (!ics)
		return -EINVAL;
	state = &ics->irq_state[src];

	icp = kvmppc_xics_find_server(kvm, server);
	if (!icp)
		return -EINVAL;

	XICS_DBG("set_xive %#x server %#x prio %#x MP:%d RS:%d\n",
		 irq, server, priority,
		 state->masked_pending, state->resend);

	if (write_xive(xics, ics, state, server, priority, priority))
		icp_deliver_irq(xics, icp, irq, false);

	return 0;
}