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
typedef  int u32 ;
struct fw_ohci {int dummy; } ;
struct context {int running; int /*<<< orphan*/  regs; struct fw_ohci* ohci; } ;

/* Variables and functions */
 int CONTEXT_ACTIVE ; 
 int /*<<< orphan*/  CONTEXT_RUN ; 
 int /*<<< orphan*/  CONTROL_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONTROL_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohci_err (struct fw_ohci*,char*,int) ; 
 int reg_read (struct fw_ohci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct fw_ohci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void context_stop(struct context *ctx)
{
	struct fw_ohci *ohci = ctx->ohci;
	u32 reg;
	int i;

	reg_write(ohci, CONTROL_CLEAR(ctx->regs), CONTEXT_RUN);
	ctx->running = false;

	for (i = 0; i < 1000; i++) {
		reg = reg_read(ohci, CONTROL_SET(ctx->regs));
		if ((reg & CONTEXT_ACTIVE) == 0)
			return;

		if (i)
			udelay(10);
	}
	ohci_err(ohci, "DMA context still active (0x%08x)\n", reg);
}