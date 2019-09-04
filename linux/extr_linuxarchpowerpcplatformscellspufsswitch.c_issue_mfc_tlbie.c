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
struct spu_state {int dummy; } ;
struct spu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  spu_tlb_invalidate (struct spu*) ; 

__attribute__((used)) static inline void issue_mfc_tlbie(struct spu_state *csa, struct spu *spu)
{
	/* Save, Step 17:
	 * Restore, Step 12.
	 * Restore, Step 48.
	 *     Write TLB_Invalidate_Entry[IS,VPN,L,Lp]=0 register.
	 *     Then issue a PPE sync instruction.
	 */
	spu_tlb_invalidate(spu);
	mb();
}