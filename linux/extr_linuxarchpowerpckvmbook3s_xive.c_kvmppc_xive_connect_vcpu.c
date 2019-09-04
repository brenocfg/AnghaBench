#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct xive_q {int dummy; } ;
struct kvmppc_xive_vcpu {int server_num; int mfrr; int valid; int vp_cam; int vp_ipi; int /*<<< orphan*/  vp_ipi_data; int /*<<< orphan*/  vp_id; struct xive_q* queues; int /*<<< orphan*/  vp_chip_id; struct kvm_vcpu* vcpu; struct kvmppc_xive* xive; } ;
struct kvmppc_xive {int qmap; scalar_t__ single_escalation; TYPE_4__* kvm; } ;
struct TYPE_6__ {int /*<<< orphan*/  w01; } ;
struct TYPE_7__ {scalar_t__ irq_type; int /*<<< orphan*/  xive_cam_word; TYPE_2__ xive_saved_state; struct kvmppc_xive_vcpu* xive_vcpu; } ;
struct kvm_vcpu {TYPE_3__ arch; TYPE_4__* kvm; } ;
struct kvm_device {int /*<<< orphan*/ * ops; struct kvmppc_xive* private; } ;
struct TYPE_5__ {int emul_smt_mode; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; TYPE_1__ arch; } ;

/* Variables and functions */
 int EBUSY ; 
 int EEXIST ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ KVMPPC_IRQ_XICS ; 
 int KVMPPC_XIVE_Q_COUNT ; 
 int KVM_MAX_VCPUS ; 
 int TM_QW1W2_VO ; 
 int /*<<< orphan*/  XICS_IPI ; 
 int /*<<< orphan*/  XIVE_ESB_SET_PQ_00 ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/  kvm_xive_ops ; 
 int /*<<< orphan*/  kvmppc_xive_cleanup_vcpu (struct kvm_vcpu*) ; 
 scalar_t__ kvmppc_xive_find_server (TYPE_4__*,int) ; 
 struct kvmppc_xive_vcpu* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_devel (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int xive_attach_escalation (struct kvm_vcpu*,int) ; 
 int xive_native_alloc_irq () ; 
 int xive_native_configure_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xive_native_configure_queue (int /*<<< orphan*/ ,struct xive_q*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int xive_native_enable_vp (int /*<<< orphan*/ ,scalar_t__) ; 
 int xive_native_get_vp_info (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int xive_native_populate_irq_data (int,int /*<<< orphan*/ *) ; 
 int xive_provision_queue (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  xive_vm_esb_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xive_vp (struct kvmppc_xive*,int) ; 

int kvmppc_xive_connect_vcpu(struct kvm_device *dev,
			     struct kvm_vcpu *vcpu, u32 cpu)
{
	struct kvmppc_xive *xive = dev->private;
	struct kvmppc_xive_vcpu *xc;
	int i, r = -EBUSY;

	pr_devel("connect_vcpu(cpu=%d)\n", cpu);

	if (dev->ops != &kvm_xive_ops) {
		pr_devel("Wrong ops !\n");
		return -EPERM;
	}
	if (xive->kvm != vcpu->kvm)
		return -EPERM;
	if (vcpu->arch.irq_type)
		return -EBUSY;
	if (kvmppc_xive_find_server(vcpu->kvm, cpu)) {
		pr_devel("Duplicate !\n");
		return -EEXIST;
	}
	if (cpu >= (KVM_MAX_VCPUS * vcpu->kvm->arch.emul_smt_mode)) {
		pr_devel("Out of bounds !\n");
		return -EINVAL;
	}
	xc = kzalloc(sizeof(*xc), GFP_KERNEL);
	if (!xc)
		return -ENOMEM;

	/* We need to synchronize with queue provisioning */
	mutex_lock(&vcpu->kvm->lock);
	vcpu->arch.xive_vcpu = xc;
	xc->xive = xive;
	xc->vcpu = vcpu;
	xc->server_num = cpu;
	xc->vp_id = xive_vp(xive, cpu);
	xc->mfrr = 0xff;
	xc->valid = true;

	r = xive_native_get_vp_info(xc->vp_id, &xc->vp_cam, &xc->vp_chip_id);
	if (r)
		goto bail;

	/* Configure VCPU fields for use by assembly push/pull */
	vcpu->arch.xive_saved_state.w01 = cpu_to_be64(0xff000000);
	vcpu->arch.xive_cam_word = cpu_to_be32(xc->vp_cam | TM_QW1W2_VO);

	/* Allocate IPI */
	xc->vp_ipi = xive_native_alloc_irq();
	if (!xc->vp_ipi) {
		pr_err("Failed to allocate xive irq for VCPU IPI\n");
		r = -EIO;
		goto bail;
	}
	pr_devel(" IPI=0x%x\n", xc->vp_ipi);

	r = xive_native_populate_irq_data(xc->vp_ipi, &xc->vp_ipi_data);
	if (r)
		goto bail;

	/*
	 * Enable the VP first as the single escalation mode will
	 * affect escalation interrupts numbering
	 */
	r = xive_native_enable_vp(xc->vp_id, xive->single_escalation);
	if (r) {
		pr_err("Failed to enable VP in OPAL, err %d\n", r);
		goto bail;
	}

	/*
	 * Initialize queues. Initially we set them all for no queueing
	 * and we enable escalation for queue 0 only which we'll use for
	 * our mfrr change notifications. If the VCPU is hot-plugged, we
	 * do handle provisioning however based on the existing "map"
	 * of enabled queues.
	 */
	for (i = 0; i < KVMPPC_XIVE_Q_COUNT; i++) {
		struct xive_q *q = &xc->queues[i];

		/* Single escalation, no queue 7 */
		if (i == 7 && xive->single_escalation)
			break;

		/* Is queue already enabled ? Provision it */
		if (xive->qmap & (1 << i)) {
			r = xive_provision_queue(vcpu, i);
			if (r == 0 && !xive->single_escalation)
				xive_attach_escalation(vcpu, i);
			if (r)
				goto bail;
		} else {
			r = xive_native_configure_queue(xc->vp_id,
							q, i, NULL, 0, true);
			if (r) {
				pr_err("Failed to configure queue %d for VCPU %d\n",
				       i, cpu);
				goto bail;
			}
		}
	}

	/* If not done above, attach priority 0 escalation */
	r = xive_attach_escalation(vcpu, 0);
	if (r)
		goto bail;

	/* Route the IPI */
	r = xive_native_configure_irq(xc->vp_ipi, xc->vp_id, 0, XICS_IPI);
	if (!r)
		xive_vm_esb_load(&xc->vp_ipi_data, XIVE_ESB_SET_PQ_00);

bail:
	mutex_unlock(&vcpu->kvm->lock);
	if (r) {
		kvmppc_xive_cleanup_vcpu(vcpu);
		return r;
	}

	vcpu->arch.irq_type = KVMPPC_IRQ_XICS;
	return 0;
}