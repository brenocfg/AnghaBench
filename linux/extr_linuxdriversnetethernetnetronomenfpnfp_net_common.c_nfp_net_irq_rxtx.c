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
struct nfp_net_r_vector {int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  napi_schedule_irqoff (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t nfp_net_irq_rxtx(int irq, void *data)
{
	struct nfp_net_r_vector *r_vec = data;

	napi_schedule_irqoff(&r_vec->napi);

	/* The FW auto-masks any interrupt, either via the MASK bit in
	 * the MSI-X table or via the per entry ICR field.  So there
	 * is no need to disable interrupts here.
	 */
	return IRQ_HANDLED;
}