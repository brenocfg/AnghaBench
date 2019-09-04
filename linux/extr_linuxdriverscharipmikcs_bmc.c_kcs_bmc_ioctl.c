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
struct kcs_bmc {int /*<<< orphan*/  lock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 long EINVAL ; 
#define  IPMI_BMC_IOCTL_CLEAR_SMS_ATN 130 
#define  IPMI_BMC_IOCTL_FORCE_ABORT 129 
#define  IPMI_BMC_IOCTL_SET_SMS_ATN 128 
 int /*<<< orphan*/  KCS_STATUS_SMS_ATN ; 
 int /*<<< orphan*/  kcs_force_abort (struct kcs_bmc*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct kcs_bmc* to_kcs_bmc (struct file*) ; 
 int /*<<< orphan*/  update_status_bits (struct kcs_bmc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long kcs_bmc_ioctl(struct file *filp, unsigned int cmd,
			  unsigned long arg)
{
	struct kcs_bmc *kcs_bmc = to_kcs_bmc(filp);
	long ret = 0;

	spin_lock_irq(&kcs_bmc->lock);

	switch (cmd) {
	case IPMI_BMC_IOCTL_SET_SMS_ATN:
		update_status_bits(kcs_bmc, KCS_STATUS_SMS_ATN,
				   KCS_STATUS_SMS_ATN);
		break;

	case IPMI_BMC_IOCTL_CLEAR_SMS_ATN:
		update_status_bits(kcs_bmc, KCS_STATUS_SMS_ATN,
				   0);
		break;

	case IPMI_BMC_IOCTL_FORCE_ABORT:
		kcs_force_abort(kcs_bmc);
		break;

	default:
		ret = -EINVAL;
		break;
	}

	spin_unlock_irq(&kcs_bmc->lock);

	return ret;
}