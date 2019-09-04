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
struct s5p_mfc_dev {int /*<<< orphan*/  mfc_regs; } ;

/* Variables and functions */
 scalar_t__ IS_MFCV6_PLUS (struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  s5p_mfc_init_regs_v6_plus (struct s5p_mfc_dev*) ; 

void s5p_mfc_init_regs(struct s5p_mfc_dev *dev)
{
	if (IS_MFCV6_PLUS(dev))
		dev->mfc_regs = s5p_mfc_init_regs_v6_plus(dev);
}