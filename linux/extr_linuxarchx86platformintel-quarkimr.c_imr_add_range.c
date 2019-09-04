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
struct imr_regs {unsigned int rmask; unsigned int wmask; void* addr_hi; void* addr_lo; } ;
struct imr_device {int init; unsigned int max_imr; int /*<<< orphan*/  lock; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 unsigned int IMR_READ_ACCESS_ALL ; 
 unsigned int IMR_WRITE_ACCESS_ALL ; 
 scalar_t__ WARN_ONCE (int,char*) ; 
 scalar_t__ imr_address_overlap (scalar_t__,struct imr_regs*) ; 
 int imr_check_params (scalar_t__,size_t) ; 
 struct imr_device imr_dev ; 
 scalar_t__ imr_is_enabled (struct imr_regs*) ; 
 size_t imr_raw_size (size_t) ; 
 int imr_read (struct imr_device*,unsigned int,struct imr_regs*) ; 
 int imr_write (struct imr_device*,int,struct imr_regs*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* phys_to_imr (scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int,scalar_t__*,scalar_t__*,size_t,unsigned int,unsigned int) ; 

int imr_add_range(phys_addr_t base, size_t size,
		  unsigned int rmask, unsigned int wmask)
{
	phys_addr_t end;
	unsigned int i;
	struct imr_device *idev = &imr_dev;
	struct imr_regs imr;
	size_t raw_size;
	int reg;
	int ret;

	if (WARN_ONCE(idev->init == false, "driver not initialized"))
		return -ENODEV;

	ret = imr_check_params(base, size);
	if (ret)
		return ret;

	/* Tweak the size value. */
	raw_size = imr_raw_size(size);
	end = base + raw_size;

	/*
	 * Check for reserved IMR value common to firmware, kernel and grub
	 * indicating a disabled IMR.
	 */
	imr.addr_lo = phys_to_imr(base);
	imr.addr_hi = phys_to_imr(end);
	imr.rmask = rmask;
	imr.wmask = wmask;
	if (!imr_is_enabled(&imr))
		return -ENOTSUPP;

	mutex_lock(&idev->lock);

	/*
	 * Find a free IMR while checking for an existing overlapping range.
	 * Note there's no restriction in silicon to prevent IMR overlaps.
	 * For the sake of simplicity and ease in defining/debugging an IMR
	 * memory map we exclude IMR overlaps.
	 */
	reg = -1;
	for (i = 0; i < idev->max_imr; i++) {
		ret = imr_read(idev, i, &imr);
		if (ret)
			goto failed;

		/* Find overlap @ base or end of requested range. */
		ret = -EINVAL;
		if (imr_is_enabled(&imr)) {
			if (imr_address_overlap(base, &imr))
				goto failed;
			if (imr_address_overlap(end, &imr))
				goto failed;
		} else {
			reg = i;
		}
	}

	/* Error out if we have no free IMR entries. */
	if (reg == -1) {
		ret = -ENOMEM;
		goto failed;
	}

	pr_debug("add %d phys %pa-%pa size %zx mask 0x%08x wmask 0x%08x\n",
		 reg, &base, &end, raw_size, rmask, wmask);

	/* Enable IMR at specified range and access mask. */
	imr.addr_lo = phys_to_imr(base);
	imr.addr_hi = phys_to_imr(end);
	imr.rmask = rmask;
	imr.wmask = wmask;

	ret = imr_write(idev, reg, &imr);
	if (ret < 0) {
		/*
		 * In the highly unlikely event iosf_mbi_write failed
		 * attempt to rollback the IMR setup skipping the trapping
		 * of further IOSF write failures.
		 */
		imr.addr_lo = 0;
		imr.addr_hi = 0;
		imr.rmask = IMR_READ_ACCESS_ALL;
		imr.wmask = IMR_WRITE_ACCESS_ALL;
		imr_write(idev, reg, &imr);
	}
failed:
	mutex_unlock(&idev->lock);
	return ret;
}