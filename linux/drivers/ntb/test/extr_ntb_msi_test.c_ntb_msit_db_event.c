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
typedef  int u64 ;
typedef  int u32 ;
struct ntb_msit_ctx {TYPE_1__* peers; int /*<<< orphan*/  ntb; } ;
struct ntb_msi_desc {int dummy; } ;
typedef  int /*<<< orphan*/  peer_mask ;
struct TYPE_2__ {int num_irqs; struct ntb_msi_desc* msi_desc; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct ntb_msi_desc* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ntb_msi_desc*) ; 
 int /*<<< orphan*/  ntb_db_clear (int /*<<< orphan*/ ,int) ; 
 int ntb_db_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_msit_copy_peer_desc (struct ntb_msit_ctx*,int) ; 
 int ntb_peer_spad_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ntb_msit_db_event(void *ctx, int vec)
{
	struct ntb_msit_ctx *nm = ctx;
	struct ntb_msi_desc *desc;
	u64 peer_mask = ntb_db_read(nm->ntb);
	u32 irq_count;
	int peer;

	ntb_db_clear(nm->ntb, peer_mask);

	for (peer = 0; peer < sizeof(peer_mask) * 8; peer++) {
		if (!(peer_mask & BIT(peer)))
			continue;

		irq_count = ntb_peer_spad_read(nm->ntb, peer, 0);
		if (irq_count == -1)
			continue;

		desc = kcalloc(irq_count, sizeof(*desc), GFP_ATOMIC);
		if (!desc)
			continue;

		kfree(nm->peers[peer].msi_desc);
		nm->peers[peer].msi_desc = desc;
		nm->peers[peer].num_irqs = irq_count;

		ntb_msit_copy_peer_desc(nm, peer);
	}
}