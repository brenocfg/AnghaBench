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
typedef  size_t u32 ;
struct spu {int /*<<< orphan*/  aff_list; int /*<<< orphan*/  has_mem_affinity; } ;

/* Variables and functions */
 int MAX_NUMNODES ; 
 int QS20_SPES_PER_BE ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t* qs20_reg_idxs ; 
 int /*<<< orphan*/ * qs20_reg_memory ; 
 struct spu* spu_lookup_reg (int,size_t) ; 

__attribute__((used)) static void init_affinity_qs20_harcoded(void)
{
	int node, i;
	struct spu *last_spu, *spu;
	u32 reg;

	for (node = 0; node < MAX_NUMNODES; node++) {
		last_spu = NULL;
		for (i = 0; i < QS20_SPES_PER_BE; i++) {
			reg = qs20_reg_idxs[i];
			spu = spu_lookup_reg(node, reg);
			if (!spu)
				continue;
			spu->has_mem_affinity = qs20_reg_memory[reg];
			if (last_spu)
				list_add_tail(&spu->aff_list,
						&last_spu->aff_list);
			last_spu = spu;
		}
	}
}