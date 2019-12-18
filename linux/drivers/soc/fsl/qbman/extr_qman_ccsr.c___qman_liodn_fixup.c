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
typedef  int u16 ;

/* Variables and functions */
 int LIO_CFG_LIODN_MASK ; 
 int QMAN_REV30 ; 
 int QM_CHANNEL_SWPORTAL0 ; 
 int /*<<< orphan*/  REG_QCSP_LIO_CFG (int) ; 
 int /*<<< orphan*/  REG_REV3_QCSP_LIO_CFG (int) ; 
 int qm_ccsr_in (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_ccsr_out (int /*<<< orphan*/ ,int) ; 
 int qman_ip_rev ; 

void __qman_liodn_fixup(u16 channel)
{
	static int done;
	static u32 liodn_offset;
	u32 before, after;
	int idx = channel - QM_CHANNEL_SWPORTAL0;

	if ((qman_ip_rev & 0xFF00) >= QMAN_REV30)
		before = qm_ccsr_in(REG_REV3_QCSP_LIO_CFG(idx));
	else
		before = qm_ccsr_in(REG_QCSP_LIO_CFG(idx));
	if (!done) {
		liodn_offset = before & LIO_CFG_LIODN_MASK;
		done = 1;
		return;
	}
	after = (before & (~LIO_CFG_LIODN_MASK)) | liodn_offset;
	if ((qman_ip_rev & 0xFF00) >= QMAN_REV30)
		qm_ccsr_out(REG_REV3_QCSP_LIO_CFG(idx), after);
	else
		qm_ccsr_out(REG_QCSP_LIO_CFG(idx), after);
}