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
struct kvmppc_xics {int max_icsid; struct kvmppc_ics** ics; } ;
struct kvmppc_ics {int icsid; TYPE_1__* irq_state; } ;
struct kvm {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int number; void* saved_priority; void* priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int KVMPPC_XICS_ICS_SHIFT ; 
 int KVMPPC_XICS_IRQ_PER_ICS ; 
 void* MASKED ; 
 struct kvmppc_ics* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static struct kvmppc_ics *kvmppc_xics_create_ics(struct kvm *kvm,
					struct kvmppc_xics *xics, int irq)
{
	struct kvmppc_ics *ics;
	int i, icsid;

	icsid = irq >> KVMPPC_XICS_ICS_SHIFT;

	mutex_lock(&kvm->lock);

	/* ICS already exists - somebody else got here first */
	if (xics->ics[icsid])
		goto out;

	/* Create the ICS */
	ics = kzalloc(sizeof(struct kvmppc_ics), GFP_KERNEL);
	if (!ics)
		goto out;

	ics->icsid = icsid;

	for (i = 0; i < KVMPPC_XICS_IRQ_PER_ICS; i++) {
		ics->irq_state[i].number = (icsid << KVMPPC_XICS_ICS_SHIFT) | i;
		ics->irq_state[i].priority = MASKED;
		ics->irq_state[i].saved_priority = MASKED;
	}
	smp_wmb();
	xics->ics[icsid] = ics;

	if (icsid > xics->max_icsid)
		xics->max_icsid = icsid;

 out:
	mutex_unlock(&kvm->lock);
	return xics->ics[icsid];
}