#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ntb_msit_ctx {TYPE_1__* peers; TYPE_2__* ntb; } ;
struct ntb_msi_desc {void* data; void* addr_offset; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int num_irqs; int /*<<< orphan*/  init_comp; struct ntb_msi_desc* msi_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 void* ntb_peer_spad_read (TYPE_2__*,int,int) ; 

__attribute__((used)) static void ntb_msit_copy_peer_desc(struct ntb_msit_ctx *nm, int peer)
{
	int i;
	struct ntb_msi_desc *desc = nm->peers[peer].msi_desc;
	int irq_count = nm->peers[peer].num_irqs;

	for (i = 0; i < irq_count; i++) {
		desc[i].addr_offset = ntb_peer_spad_read(nm->ntb, peer,
							 2 * i + 1);
		desc[i].data = ntb_peer_spad_read(nm->ntb, peer, 2 * i + 2);
	}

	dev_info(&nm->ntb->dev, "Found %d interrupts on peer %d\n",
		 irq_count, peer);

	complete_all(&nm->peers[peer].init_comp);
}