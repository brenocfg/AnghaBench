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
struct descriptor {int /*<<< orphan*/  branch_address; scalar_t__ transfer_status; int /*<<< orphan*/  res_count; } ;
struct ar_context {size_t last_buffer_index; int /*<<< orphan*/  regs; int /*<<< orphan*/  ohci; struct descriptor* descriptors; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_WAKE ; 
 int /*<<< orphan*/  CONTROL_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void ar_context_link_page(struct ar_context *ctx, unsigned int index)
{
	struct descriptor *d;

	d = &ctx->descriptors[index];
	d->branch_address  &= cpu_to_le32(~0xf);
	d->res_count       =  cpu_to_le16(PAGE_SIZE);
	d->transfer_status =  0;

	wmb(); /* finish init of new descriptors before branch_address update */
	d = &ctx->descriptors[ctx->last_buffer_index];
	d->branch_address  |= cpu_to_le32(1);

	ctx->last_buffer_index = index;

	reg_write(ctx->ohci, CONTROL_SET(ctx->regs), CONTEXT_WAKE);
}