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
struct fw_ohci {int dummy; } ;
struct ar_context {int /*<<< orphan*/  regs; struct fw_ohci* ohci; } ;

/* Variables and functions */
 int CONTEXT_RUN ; 
 int /*<<< orphan*/  CONTROL_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_writes (struct fw_ohci*) ; 
 int /*<<< orphan*/  ohci_err (struct fw_ohci*,char*,char const*) ; 
 int reg_read (struct fw_ohci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct fw_ohci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ar_context_abort(struct ar_context *ctx, const char *error_msg)
{
	struct fw_ohci *ohci = ctx->ohci;

	if (reg_read(ohci, CONTROL_CLEAR(ctx->regs)) & CONTEXT_RUN) {
		reg_write(ohci, CONTROL_CLEAR(ctx->regs), CONTEXT_RUN);
		flush_writes(ohci);

		ohci_err(ohci, "AR error: %s; DMA stopped\n", error_msg);
	}
	/* FIXME: restart? */
}