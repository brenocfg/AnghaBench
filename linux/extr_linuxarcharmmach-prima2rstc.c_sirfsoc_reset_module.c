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
struct reset_controller_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SIRFSOC_RSTBIT_NUM ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  rstc_lock ; 
 scalar_t__ sirfsoc_rstc_base ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int sirfsoc_reset_module(struct reset_controller_dev *rcdev,
					unsigned long sw_reset_idx)
{
	u32 reset_bit = sw_reset_idx;

	if (reset_bit >= SIRFSOC_RSTBIT_NUM)
		return -EINVAL;

	mutex_lock(&rstc_lock);

	/*
	 * Writing 1 to this bit resets corresponding block.
	 * Writing 0 to this bit de-asserts reset signal of the
	 * corresponding block. datasheet doesn't require explicit
	 * delay between the set and clear of reset bit. it could
	 * be shorter if tests pass.
	 */
	writel(readl(sirfsoc_rstc_base +
			(reset_bit / 32) * 4) | (1 << reset_bit),
		sirfsoc_rstc_base + (reset_bit / 32) * 4);
	msleep(20);
	writel(readl(sirfsoc_rstc_base +
			(reset_bit / 32) * 4) & ~(1 << reset_bit),
		sirfsoc_rstc_base + (reset_bit / 32) * 4);

	mutex_unlock(&rstc_lock);

	return 0;
}