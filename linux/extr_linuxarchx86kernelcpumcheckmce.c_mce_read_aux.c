#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct mce {int status; int addr; void* synd; void* ipid; void* misc; } ;
struct TYPE_6__ {scalar_t__ ser; } ;
struct TYPE_5__ {scalar_t__ smca; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* addr ) (int) ;int /*<<< orphan*/  (* misc ) (int) ;} ;

/* Variables and functions */
 int GENMASK_ULL (int,int) ; 
 int MCI_MISC_ADDR_LSB (void*) ; 
 int MCI_STATUS_ADDRV ; 
 int MCI_STATUS_MISCV ; 
 int MCI_STATUS_SYNDV ; 
 int /*<<< orphan*/  MSR_AMD64_SMCA_MCx_IPID (int) ; 
 int /*<<< orphan*/  MSR_AMD64_SMCA_MCx_SYND (int) ; 
 TYPE_3__ mca_cfg ; 
 TYPE_2__ mce_flags ; 
 void* mce_rdmsrl (int /*<<< orphan*/ ) ; 
 TYPE_1__ msr_ops ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 

__attribute__((used)) static void mce_read_aux(struct mce *m, int i)
{
	if (m->status & MCI_STATUS_MISCV)
		m->misc = mce_rdmsrl(msr_ops.misc(i));

	if (m->status & MCI_STATUS_ADDRV) {
		m->addr = mce_rdmsrl(msr_ops.addr(i));

		/*
		 * Mask the reported address by the reported granularity.
		 */
		if (mca_cfg.ser && (m->status & MCI_STATUS_MISCV)) {
			u8 shift = MCI_MISC_ADDR_LSB(m->misc);
			m->addr >>= shift;
			m->addr <<= shift;
		}

		/*
		 * Extract [55:<lsb>] where lsb is the least significant
		 * *valid* bit of the address bits.
		 */
		if (mce_flags.smca) {
			u8 lsb = (m->addr >> 56) & 0x3f;

			m->addr &= GENMASK_ULL(55, lsb);
		}
	}

	if (mce_flags.smca) {
		m->ipid = mce_rdmsrl(MSR_AMD64_SMCA_MCx_IPID(i));

		if (m->status & MCI_STATUS_SYNDV)
			m->synd = mce_rdmsrl(MSR_AMD64_SMCA_MCx_SYND(i));
	}
}