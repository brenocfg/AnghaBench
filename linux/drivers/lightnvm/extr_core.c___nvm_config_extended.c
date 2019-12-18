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
struct nvm_ioctl_create_extended {int lun_begin; int lun_end; int op; } ;
struct TYPE_2__ {int all_luns; } ;
struct nvm_dev {TYPE_1__ geo; } ;

/* Variables and functions */
 int EINVAL ; 
 int NVM_TARGET_DEFAULT_OP ; 
 int NVM_TARGET_MAX_OP ; 
 int NVM_TARGET_MIN_OP ; 
 int nvm_config_check_luns (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int __nvm_config_extended(struct nvm_dev *dev,
				 struct nvm_ioctl_create_extended *e)
{
	if (e->lun_begin == 0xFFFF && e->lun_end == 0xFFFF) {
		e->lun_begin = 0;
		e->lun_end = dev->geo.all_luns - 1;
	}

	/* op not set falls into target's default */
	if (e->op == 0xFFFF) {
		e->op = NVM_TARGET_DEFAULT_OP;
	} else if (e->op < NVM_TARGET_MIN_OP || e->op > NVM_TARGET_MAX_OP) {
		pr_err("invalid over provisioning value\n");
		return -EINVAL;
	}

	return nvm_config_check_luns(&dev->geo, e->lun_begin, e->lun_end);
}