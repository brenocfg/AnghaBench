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
struct TYPE_2__ {int /*<<< orphan*/ * slot; } ;

/* Variables and functions */
 unsigned int LSCSA_QW_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPU_RdSRR0 ; 
 TYPE_1__* regs_spill ; 
 int /*<<< orphan*/  spu_readch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srr0 ; 

__attribute__((used)) static inline void save_srr0(void)
{
	unsigned int offset;

	/* Save, Step 11:
	 *    Read and save the SPU_WSRR0 channel data to
	 *    the LSCSA.
	 */
	offset = LSCSA_QW_OFFSET(srr0);
	regs_spill[offset].slot[0] = spu_readch(SPU_RdSRR0);
}