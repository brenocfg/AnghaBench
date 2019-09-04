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
typedef  int u32 ;
struct openpic {int model; int brr1; int nb_irqs; int /*<<< orphan*/  mpic_mode_mask; int /*<<< orphan*/  flags; int /*<<< orphan*/ * fsl; int /*<<< orphan*/  lock; struct kvm_device* dev; TYPE_2__* kvm; } ;
struct kvm_device {TYPE_2__* kvm; struct openpic* private; } ;
struct TYPE_3__ {struct openpic* mpic; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GCR_MODE_MIXED ; 
 int /*<<< orphan*/  GCR_MODE_PROXY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  KVM_DEV_TYPE_FSL_MPIC_20 129 
#define  KVM_DEV_TYPE_FSL_MPIC_42 128 
 int /*<<< orphan*/  OPENPIC_FLAG_IDR_CRIT ; 
 int /*<<< orphan*/  OPENPIC_FLAG_ILR ; 
 int /*<<< orphan*/  add_mmio_region (struct openpic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_common_init (struct openpic*) ; 
 int /*<<< orphan*/  fsl_mpic_20 ; 
 int /*<<< orphan*/  fsl_mpic_42 ; 
 int /*<<< orphan*/  kfree (struct openpic*) ; 
 struct openpic* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mpic_set_default_irq_routing (struct openpic*) ; 
 int /*<<< orphan*/  openpic_cpu_mmio ; 
 int /*<<< orphan*/  openpic_gbl_mmio ; 
 int /*<<< orphan*/  openpic_reset (struct openpic*) ; 
 int /*<<< orphan*/  openpic_src_mmio ; 
 int /*<<< orphan*/  openpic_tmr_mmio ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mpic_create(struct kvm_device *dev, u32 type)
{
	struct openpic *opp;
	int ret;

	/* We only support one MPIC at a time for now */
	if (dev->kvm->arch.mpic)
		return -EINVAL;

	opp = kzalloc(sizeof(struct openpic), GFP_KERNEL);
	if (!opp)
		return -ENOMEM;

	dev->private = opp;
	opp->kvm = dev->kvm;
	opp->dev = dev;
	opp->model = type;
	spin_lock_init(&opp->lock);

	add_mmio_region(opp, &openpic_gbl_mmio);
	add_mmio_region(opp, &openpic_tmr_mmio);
	add_mmio_region(opp, &openpic_src_mmio);
	add_mmio_region(opp, &openpic_cpu_mmio);

	switch (opp->model) {
	case KVM_DEV_TYPE_FSL_MPIC_20:
		opp->fsl = &fsl_mpic_20;
		opp->brr1 = 0x00400200;
		opp->flags |= OPENPIC_FLAG_IDR_CRIT;
		opp->nb_irqs = 80;
		opp->mpic_mode_mask = GCR_MODE_MIXED;

		fsl_common_init(opp);

		break;

	case KVM_DEV_TYPE_FSL_MPIC_42:
		opp->fsl = &fsl_mpic_42;
		opp->brr1 = 0x00400402;
		opp->flags |= OPENPIC_FLAG_ILR;
		opp->nb_irqs = 196;
		opp->mpic_mode_mask = GCR_MODE_PROXY;

		fsl_common_init(opp);

		break;

	default:
		ret = -ENODEV;
		goto err;
	}

	ret = mpic_set_default_irq_routing(opp);
	if (ret)
		goto err;

	openpic_reset(opp);

	smp_wmb();
	dev->kvm->arch.mpic = opp;

	return 0;

err:
	kfree(opp);
	return ret;
}