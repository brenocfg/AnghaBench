#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ntb_msit_ctx {TYPE_3__* ntb; TYPE_2__* isr_ctx; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; int /*<<< orphan*/  addr_offset; } ;
struct TYPE_7__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ntb_peer_db_set (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_port_number (TYPE_3__*) ; 
 int /*<<< orphan*/  ntb_spad_write (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int num_irqs ; 

__attribute__((used)) static void ntb_msit_desc_changed(void *ctx)
{
	struct ntb_msit_ctx *nm = ctx;
	int i;

	dev_dbg(&nm->ntb->dev, "MSI Descriptors Changed\n");

	for (i = 0; i < num_irqs; i++) {
		ntb_spad_write(nm->ntb, 2 * i + 1,
			       nm->isr_ctx[i].desc.addr_offset);
		ntb_spad_write(nm->ntb, 2 * i + 2,
			       nm->isr_ctx[i].desc.data);
	}

	ntb_peer_db_set(nm->ntb, BIT(ntb_port_number(nm->ntb)));
}