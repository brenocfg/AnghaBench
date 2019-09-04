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
struct kvm_vcpu {int dummy; } ;
struct kvm_hw_wp_info_arch {scalar_t__ len; int /*<<< orphan*/ * old_data; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  addr; } ;
struct kvm_hw_breakpoint {scalar_t__ len; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MAX_WP_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int read_guest_abs (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int __import_wp_info(struct kvm_vcpu *vcpu,
			    struct kvm_hw_breakpoint *bp_data,
			    struct kvm_hw_wp_info_arch *wp_info)
{
	int ret = 0;
	wp_info->len = bp_data->len;
	wp_info->addr = bp_data->addr;
	wp_info->phys_addr = bp_data->phys_addr;
	wp_info->old_data = NULL;

	if (wp_info->len < 0 || wp_info->len > MAX_WP_SIZE)
		return -EINVAL;

	wp_info->old_data = kmalloc(bp_data->len, GFP_KERNEL);
	if (!wp_info->old_data)
		return -ENOMEM;
	/* try to backup the original value */
	ret = read_guest_abs(vcpu, wp_info->phys_addr, wp_info->old_data,
			     wp_info->len);
	if (ret) {
		kfree(wp_info->old_data);
		wp_info->old_data = NULL;
	}

	return ret;
}