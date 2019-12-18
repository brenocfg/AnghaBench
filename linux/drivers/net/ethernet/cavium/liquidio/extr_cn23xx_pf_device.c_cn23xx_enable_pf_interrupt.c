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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {scalar_t__ max_vfs; } ;
struct octeon_device {scalar_t__ rev_id; TYPE_1__ sriov_info; scalar_t__ chip; } ;
struct octeon_cn23xx_pf {int /*<<< orphan*/  intr_enb_reg64; int /*<<< orphan*/  intr_mask64; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN23XX_INTR_PKT_DATA ; 
 int /*<<< orphan*/  CN23XX_INTR_VF_MBOX ; 
 int OCTEON_ALL_INTR ; 
 scalar_t__ OCTEON_CN23XX_REV_1_1 ; 
 int OCTEON_MBOX_INTR ; 
 int OCTEON_OUTPUT_INTR ; 
 int /*<<< orphan*/  readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cn23xx_enable_pf_interrupt(struct octeon_device *oct, u8 intr_flag)
{
	struct octeon_cn23xx_pf *cn23xx = (struct octeon_cn23xx_pf *)oct->chip;
	u64 intr_val = 0;

	/*  Divide the single write to multiple writes based on the flag. */
	/* Enable Interrupt */
	if (intr_flag == OCTEON_ALL_INTR) {
		writeq(cn23xx->intr_mask64, cn23xx->intr_enb_reg64);
	} else if (intr_flag & OCTEON_OUTPUT_INTR) {
		intr_val = readq(cn23xx->intr_enb_reg64);
		intr_val |= CN23XX_INTR_PKT_DATA;
		writeq(intr_val, cn23xx->intr_enb_reg64);
	} else if ((intr_flag & OCTEON_MBOX_INTR) &&
		   (oct->sriov_info.max_vfs > 0)) {
		if (oct->rev_id >= OCTEON_CN23XX_REV_1_1) {
			intr_val = readq(cn23xx->intr_enb_reg64);
			intr_val |= CN23XX_INTR_VF_MBOX;
			writeq(intr_val, cn23xx->intr_enb_reg64);
		}
	}
}