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
struct decon_context {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECON_TRIGCON ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TRIGCON_SWTRIGCMD ; 
 int /*<<< orphan*/  decon_set_bits (struct decon_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t decon_te_irq_handler(int irq, void *dev_id)
{
	struct decon_context *ctx = dev_id;

	decon_set_bits(ctx, DECON_TRIGCON, TRIGCON_SWTRIGCMD, ~0);

	return IRQ_HANDLED;
}