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
struct sdio_func {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_ENABLE_REG ; 
 int /*<<< orphan*/  INT_PENDING_REG ; 
 int /*<<< orphan*/  ks_sdio_interrupt ; 
 int sdio_claim_irq (struct sdio_func*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_writeb (struct sdio_func*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ks7010_sdio_setup_irqs(struct sdio_func *func)
{
	int ret;

	/* interrupt disable */
	sdio_writeb(func, 0, INT_ENABLE_REG, &ret);
	if (ret)
		goto irq_error;

	sdio_writeb(func, 0xff, INT_PENDING_REG, &ret);
	if (ret)
		goto irq_error;

	/* setup interrupt handler */
	ret = sdio_claim_irq(func, ks_sdio_interrupt);

irq_error:
	return ret;
}