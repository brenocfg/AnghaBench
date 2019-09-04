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
typedef  int /*<<< orphan*/  u32 ;
struct ppc440spe_adma_desc_slot {int /*<<< orphan*/  src_cnt; int /*<<< orphan*/  rxor_cursor; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ppc440spe_adma_dma2rxor_prep_src (struct ppc440spe_adma_desc_slot*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ppc440spe_adma_init_dma2rxor_slot(
		struct ppc440spe_adma_desc_slot *desc,
		dma_addr_t *src, int src_cnt)
{
	int i;

	/* initialize CDB */
	for (i = 0; i < src_cnt; i++) {
		ppc440spe_adma_dma2rxor_prep_src(desc, &desc->rxor_cursor, i,
						 desc->src_cnt, (u32)src[i]);
	}
}