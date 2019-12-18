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
struct fza_private {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  reset; int /*<<< orphan*/  control_b; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZA_CONTROL_B_IDLE ; 
 int /*<<< orphan*/  FZA_RESET_CLR ; 
 int /*<<< orphan*/  FZA_RESET_INIT ; 
 int /*<<< orphan*/  readw_o (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writew_o (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void fza_do_shutdown(struct fza_private *fp)
{
	/* Disable the driver mode. */
	writew_o(FZA_CONTROL_B_IDLE, &fp->regs->control_b);

	/* And reset the board. */
	writew_o(FZA_RESET_INIT, &fp->regs->reset);
	readw_o(&fp->regs->reset);	/* Synchronize. */
	writew_o(FZA_RESET_CLR, &fp->regs->reset);
	readw_o(&fp->regs->reset);	/* Synchronize. */
}