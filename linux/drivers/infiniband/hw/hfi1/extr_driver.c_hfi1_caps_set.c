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
struct kernel_param {scalar_t__ arg; } ;

/* Variables and functions */
 scalar_t__ HFI1_CAP_LOCKED () ; 
 unsigned long HFI1_CAP_LOCKED_SMASK ; 
 unsigned long HFI1_CAP_MUST_HAVE_KERN ; 
 unsigned long HFI1_CAP_RESERVED_MASK ; 
 unsigned long HFI1_CAP_USER_SHIFT ; 
 unsigned long HFI1_CAP_WRITABLE_MASK ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 

__attribute__((used)) static int hfi1_caps_set(const char *val, const struct kernel_param *kp)
{
	int ret = 0;
	unsigned long *cap_mask_ptr = (unsigned long *)kp->arg,
		cap_mask = *cap_mask_ptr, value, diff,
		write_mask = ((HFI1_CAP_WRITABLE_MASK << HFI1_CAP_USER_SHIFT) |
			      HFI1_CAP_WRITABLE_MASK);

	ret = kstrtoul(val, 0, &value);
	if (ret) {
		pr_warn("Invalid module parameter value for 'cap_mask'\n");
		goto done;
	}
	/* Get the changed bits (except the locked bit) */
	diff = value ^ (cap_mask & ~HFI1_CAP_LOCKED_SMASK);

	/* Remove any bits that are not allowed to change after driver load */
	if (HFI1_CAP_LOCKED() && (diff & ~write_mask)) {
		pr_warn("Ignoring non-writable capability bits %#lx\n",
			diff & ~write_mask);
		diff &= write_mask;
	}

	/* Mask off any reserved bits */
	diff &= ~HFI1_CAP_RESERVED_MASK;
	/* Clear any previously set and changing bits */
	cap_mask &= ~diff;
	/* Update the bits with the new capability */
	cap_mask |= (value & diff);
	/* Check for any kernel/user restrictions */
	diff = (cap_mask & (HFI1_CAP_MUST_HAVE_KERN << HFI1_CAP_USER_SHIFT)) ^
		((cap_mask & HFI1_CAP_MUST_HAVE_KERN) << HFI1_CAP_USER_SHIFT);
	cap_mask &= ~diff;
	/* Set the bitmask to the final set */
	*cap_mask_ptr = cap_mask;
done:
	return ret;
}