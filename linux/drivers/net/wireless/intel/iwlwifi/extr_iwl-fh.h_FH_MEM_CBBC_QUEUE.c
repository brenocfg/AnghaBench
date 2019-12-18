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
struct iwl_trans {TYPE_1__* trans_cfg; } ;
struct TYPE_2__ {scalar_t__ use_tfh; } ;

/* Variables and functions */
 unsigned int FH_MEM_CBBC_0_15_LOWER_BOUND ; 
 unsigned int FH_MEM_CBBC_16_19_LOWER_BOUND ; 
 unsigned int FH_MEM_CBBC_20_31_LOWER_BOUND ; 
 unsigned int TFH_TFDQ_CBB_TABLE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static inline unsigned int FH_MEM_CBBC_QUEUE(struct iwl_trans *trans,
					     unsigned int chnl)
{
	if (trans->trans_cfg->use_tfh) {
		WARN_ON_ONCE(chnl >= 64);
		return TFH_TFDQ_CBB_TABLE + 8 * chnl;
	}
	if (chnl < 16)
		return FH_MEM_CBBC_0_15_LOWER_BOUND + 4 * chnl;
	if (chnl < 20)
		return FH_MEM_CBBC_16_19_LOWER_BOUND + 4 * (chnl - 16);
	WARN_ON_ONCE(chnl >= 32);
	return FH_MEM_CBBC_20_31_LOWER_BOUND + 4 * (chnl - 20);
}