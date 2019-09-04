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
struct mxc_scc {int block_size_bytes; int /*<<< orphan*/  memory_size_bytes; int /*<<< orphan*/  bytes_remaining; scalar_t__ base; scalar_t__ black_memory; scalar_t__ red_memory; } ;

/* Variables and functions */
 int SCC_NON_RESERVED_OFFSET ; 
 scalar_t__ SCC_SCM_BLACK_MEMORY ; 
 scalar_t__ SCC_SCM_BLACK_START ; 
 scalar_t__ SCC_SCM_RED_MEMORY ; 
 scalar_t__ SCC_SCM_RED_START ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mxc_scc_hw_init(struct mxc_scc *scc)
{
	int offset;

	offset = SCC_NON_RESERVED_OFFSET / scc->block_size_bytes;

	/* Fill the RED_START register */
	writel(offset, scc->base + SCC_SCM_RED_START);

	/* Fill the BLACK_START register */
	writel(offset, scc->base + SCC_SCM_BLACK_START);

	scc->red_memory = scc->base + SCC_SCM_RED_MEMORY +
			  SCC_NON_RESERVED_OFFSET;

	scc->black_memory = scc->base + SCC_SCM_BLACK_MEMORY +
			    SCC_NON_RESERVED_OFFSET;

	scc->bytes_remaining = scc->memory_size_bytes;
}