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
typedef  size_t u32 ;
struct kvmppc_xive_src_block {TYPE_1__* irq_state; } ;
struct kvmppc_xive {size_t max_sbid; scalar_t__ saved_src_count; struct kvmppc_xive_src_block** src_blocks; } ;
struct TYPE_2__ {int in_queue; } ;

/* Variables and functions */
 size_t KVMPPC_XICS_IRQ_PER_ICS ; 

__attribute__((used)) static void xive_post_save_scan(struct kvmppc_xive *xive)
{
	u32 i, j;

	/* Clear all the in_queue flags */
	for (i = 0; i <= xive->max_sbid; i++) {
		struct kvmppc_xive_src_block *sb = xive->src_blocks[i];
		if (!sb)
			continue;
		for (j = 0;  j < KVMPPC_XICS_IRQ_PER_ICS; j++)
			sb->irq_state[j].in_queue = false;
	}

	/* Next get_source() will do a new scan */
	xive->saved_src_count = 0;
}