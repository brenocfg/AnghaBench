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
typedef  int u32 ;
struct imr_regs {int /*<<< orphan*/  addr_hi; int /*<<< orphan*/  addr_lo; int /*<<< orphan*/  wmask; int /*<<< orphan*/  rmask; } ;
struct imr_device {int reg_base; } ;

/* Variables and functions */
 scalar_t__ IMR_MASK ; 
 int IMR_NUM_REGS ; 
 int /*<<< orphan*/  MBI_REG_WRITE ; 
 int /*<<< orphan*/  QRK_MBI_UNIT_MM ; 
 int /*<<< orphan*/  WARN (int,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ imr_to_phys (int /*<<< orphan*/ ) ; 
 int iosf_mbi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static int imr_write(struct imr_device *idev, u32 imr_id, struct imr_regs *imr)
{
	unsigned long flags;
	u32 reg = imr_id * IMR_NUM_REGS + idev->reg_base;
	int ret;

	local_irq_save(flags);

	ret = iosf_mbi_write(QRK_MBI_UNIT_MM, MBI_REG_WRITE, reg++, imr->addr_lo);
	if (ret)
		goto failed;

	ret = iosf_mbi_write(QRK_MBI_UNIT_MM, MBI_REG_WRITE, reg++, imr->addr_hi);
	if (ret)
		goto failed;

	ret = iosf_mbi_write(QRK_MBI_UNIT_MM, MBI_REG_WRITE, reg++, imr->rmask);
	if (ret)
		goto failed;

	ret = iosf_mbi_write(QRK_MBI_UNIT_MM, MBI_REG_WRITE, reg++, imr->wmask);
	if (ret)
		goto failed;

	local_irq_restore(flags);
	return 0;
failed:
	/*
	 * If writing to the IOSF failed then we're in an unknown state,
	 * likely a very bad state. An IMR in an invalid state will almost
	 * certainly lead to a memory access violation.
	 */
	local_irq_restore(flags);
	WARN(ret, "IOSF-MBI write fail range 0x%08x-0x%08x unreliable\n",
	     imr_to_phys(imr->addr_lo), imr_to_phys(imr->addr_hi) + IMR_MASK);

	return ret;
}