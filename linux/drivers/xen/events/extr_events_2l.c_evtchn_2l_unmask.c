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
struct vcpu_info {int evtchn_upcall_pending; int /*<<< orphan*/  evtchn_pending_sel; } ;
struct shared_info {int /*<<< orphan*/ * evtchn_mask; int /*<<< orphan*/ * evtchn_pending; } ;
struct evtchn_unmask {unsigned int port; } ;

/* Variables and functions */
 unsigned int BITS_PER_EVTCHN_WORD ; 
 int /*<<< orphan*/  BM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EVTCHNOP_unmask ; 
 int /*<<< orphan*/  HYPERVISOR_event_channel_op (int /*<<< orphan*/ ,struct evtchn_unmask*) ; 
 struct shared_info* HYPERVISOR_shared_info ; 
 struct vcpu_info* __this_cpu_read (int /*<<< orphan*/ ) ; 
 unsigned int cpu_from_evtchn (unsigned int) ; 
 unsigned int get_cpu () ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  sync_clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_test_and_set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int sync_test_bit (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ xen_hvm_domain () ; 
 int /*<<< orphan*/  xen_vcpu ; 

__attribute__((used)) static void evtchn_2l_unmask(unsigned port)
{
	struct shared_info *s = HYPERVISOR_shared_info;
	unsigned int cpu = get_cpu();
	int do_hypercall = 0, evtchn_pending = 0;

	BUG_ON(!irqs_disabled());

	if (unlikely((cpu != cpu_from_evtchn(port))))
		do_hypercall = 1;
	else {
		/*
		 * Need to clear the mask before checking pending to
		 * avoid a race with an event becoming pending.
		 *
		 * EVTCHNOP_unmask will only trigger an upcall if the
		 * mask bit was set, so if a hypercall is needed
		 * remask the event.
		 */
		sync_clear_bit(port, BM(&s->evtchn_mask[0]));
		evtchn_pending = sync_test_bit(port, BM(&s->evtchn_pending[0]));

		if (unlikely(evtchn_pending && xen_hvm_domain())) {
			sync_set_bit(port, BM(&s->evtchn_mask[0]));
			do_hypercall = 1;
		}
	}

	/* Slow path (hypercall) if this is a non-local port or if this is
	 * an hvm domain and an event is pending (hvm domains don't have
	 * their own implementation of irq_enable). */
	if (do_hypercall) {
		struct evtchn_unmask unmask = { .port = port };
		(void)HYPERVISOR_event_channel_op(EVTCHNOP_unmask, &unmask);
	} else {
		struct vcpu_info *vcpu_info = __this_cpu_read(xen_vcpu);

		/*
		 * The following is basically the equivalent of
		 * 'hw_resend_irq'. Just like a real IO-APIC we 'lose
		 * the interrupt edge' if the channel is masked.
		 */
		if (evtchn_pending &&
		    !sync_test_and_set_bit(port / BITS_PER_EVTCHN_WORD,
					   BM(&vcpu_info->evtchn_pending_sel)))
			vcpu_info->evtchn_upcall_pending = 1;
	}

	put_cpu();
}