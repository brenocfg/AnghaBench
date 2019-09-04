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
struct sdio_func {int num; int /*<<< orphan*/  card; int /*<<< orphan*/ * irq_handler; } ;
typedef  int /*<<< orphan*/  sdio_irq_handler_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  SDIO_CCCR_IENx ; 
 int mmc_io_rw_direct (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,unsigned char*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int sdio_card_irq_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_func_id (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_single_irq_set (int /*<<< orphan*/ ) ; 

int sdio_claim_irq(struct sdio_func *func, sdio_irq_handler_t *handler)
{
	int ret;
	unsigned char reg;

	if (!func)
		return -EINVAL;

	pr_debug("SDIO: Enabling IRQ for %s...\n", sdio_func_id(func));

	if (func->irq_handler) {
		pr_debug("SDIO: IRQ for %s already in use.\n", sdio_func_id(func));
		return -EBUSY;
	}

	ret = mmc_io_rw_direct(func->card, 0, 0, SDIO_CCCR_IENx, 0, &reg);
	if (ret)
		return ret;

	reg |= 1 << func->num;

	reg |= 1; /* Master interrupt enable */

	ret = mmc_io_rw_direct(func->card, 1, 0, SDIO_CCCR_IENx, reg, NULL);
	if (ret)
		return ret;

	func->irq_handler = handler;
	ret = sdio_card_irq_get(func->card);
	if (ret)
		func->irq_handler = NULL;
	sdio_single_irq_set(func->card);

	return ret;
}