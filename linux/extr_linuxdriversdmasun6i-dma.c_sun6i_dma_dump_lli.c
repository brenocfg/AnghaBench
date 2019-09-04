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
struct TYPE_2__ {int /*<<< orphan*/  chan; } ;
struct sun6i_vchan {TYPE_1__ vc; } ;
struct sun6i_dma_lli {int /*<<< orphan*/  p_lli_next; int /*<<< orphan*/  para; int /*<<< orphan*/  len; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  cfg; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  chan2dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct sun6i_dma_lli*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_phys (struct sun6i_dma_lli*) ; 

__attribute__((used)) static inline void sun6i_dma_dump_lli(struct sun6i_vchan *vchan,
				      struct sun6i_dma_lli *lli)
{
	phys_addr_t p_lli = virt_to_phys(lli);

	dev_dbg(chan2dev(&vchan->vc.chan),
		"\n\tdesc:   p - %pa v - 0x%p\n"
		"\t\tc - 0x%08x s - 0x%08x d - 0x%08x\n"
		"\t\tl - 0x%08x p - 0x%08x n - 0x%08x\n",
		&p_lli, lli,
		lli->cfg, lli->src, lli->dst,
		lli->len, lli->para, lli->p_lli_next);
}