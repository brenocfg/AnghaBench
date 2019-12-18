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
typedef  int /*<<< orphan*/  u16 ;
struct zd_chip {scalar_t__ fw_regs_base; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWRAW_REGS_ADDR ; 
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_chip_dev (struct zd_chip*) ; 
 int zd_ioread16_locked (struct zd_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_fw_regs_offset(struct zd_chip *chip)
{
	int r;

	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	r = zd_ioread16_locked(chip, (u16*)&chip->fw_regs_base,
		               FWRAW_REGS_ADDR);
	if (r)
		return r;
	dev_dbg_f(zd_chip_dev(chip), "fw_regs_base: %#06hx\n",
		  (u16)chip->fw_regs_base);

	return 0;
}