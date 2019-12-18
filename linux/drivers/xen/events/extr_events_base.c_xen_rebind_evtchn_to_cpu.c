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
struct evtchn_bind_vcpu {int port; int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVTCHNOP_bind_vcpu ; 
 scalar_t__ HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_bind_vcpu*) ; 
 int /*<<< orphan*/  VALID_EVTCHN (int) ; 
 int /*<<< orphan*/  bind_evtchn_to_cpu (int,unsigned int) ; 
 int test_and_set_mask (int) ; 
 int /*<<< orphan*/  unmask_evtchn (int) ; 
 int /*<<< orphan*/  xen_support_evtchn_rebind () ; 
 int /*<<< orphan*/  xen_vcpu_nr (unsigned int) ; 

__attribute__((used)) static int xen_rebind_evtchn_to_cpu(int evtchn, unsigned int tcpu)
{
	struct evtchn_bind_vcpu bind_vcpu;
	int masked;

	if (!VALID_EVTCHN(evtchn))
		return -1;

	if (!xen_support_evtchn_rebind())
		return -1;

	/* Send future instances of this interrupt to other vcpu. */
	bind_vcpu.port = evtchn;
	bind_vcpu.vcpu = xen_vcpu_nr(tcpu);

	/*
	 * Mask the event while changing the VCPU binding to prevent
	 * it being delivered on an unexpected VCPU.
	 */
	masked = test_and_set_mask(evtchn);

	/*
	 * If this fails, it usually just indicates that we're dealing with a
	 * virq or IPI channel, which don't actually need to be rebound. Ignore
	 * it, but don't do the xenlinux-level rebind in that case.
	 */
	if (HYPERVISOR_event_channel_op(EVTCHNOP_bind_vcpu, &bind_vcpu) >= 0)
		bind_evtchn_to_cpu(evtchn, tcpu);

	if (!masked)
		unmask_evtchn(evtchn);

	return 0;
}