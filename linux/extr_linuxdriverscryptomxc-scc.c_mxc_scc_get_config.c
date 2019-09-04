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
struct mxc_scc {int block_size_bytes; int black_ram_size_blocks; scalar_t__ memory_size_bytes; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SCC_NON_RESERVED_OFFSET ; 
 scalar_t__ SCC_SCM_CFG ; 
 int SCC_SCM_CFG_BLACK_SIZE_MASK ; 
 int SCC_SCM_CFG_BLOCK_SIZE_MASK ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int mxc_scc_get_config(struct mxc_scc *scc)
{
	int config;

	config = readl(scc->base + SCC_SCM_CFG);

	scc->block_size_bytes = config & SCC_SCM_CFG_BLOCK_SIZE_MASK;

	scc->black_ram_size_blocks = config & SCC_SCM_CFG_BLACK_SIZE_MASK;

	scc->memory_size_bytes = (scc->block_size_bytes *
				  scc->black_ram_size_blocks) -
				  SCC_NON_RESERVED_OFFSET;

	return 0;
}