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
struct onenand_chip {scalar_t__ irq; int (* read_word ) (scalar_t__) ;void* wait; scalar_t__ base; int /*<<< orphan*/  (* write_word ) (int,scalar_t__) ;int /*<<< orphan*/  complete; } ;
struct mtd_info {struct onenand_chip* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ ONENAND_REG_SYS_CFG1 ; 
 int ONENAND_SYS_CFG1_IOBE ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  onenand_interrupt ; 
 void* onenand_try_interrupt_wait ; 
 void* onenand_wait ; 
 scalar_t__ request_irq (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct onenand_chip*) ; 
 int stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int,scalar_t__) ; 

__attribute__((used)) static void onenand_setup_wait(struct mtd_info *mtd)
{
	struct onenand_chip *this = mtd->priv;
	int syscfg;

	init_completion(&this->complete);

	if (this->irq <= 0) {
		this->wait = onenand_wait;
		return;
	}

	if (request_irq(this->irq, &onenand_interrupt,
				IRQF_SHARED, "onenand", this)) {
		/* If we can't get irq, use the normal wait */
		this->wait = onenand_wait;
		return;
	}

	/* Enable interrupt */
	syscfg = this->read_word(this->base + ONENAND_REG_SYS_CFG1);
	syscfg |= ONENAND_SYS_CFG1_IOBE;
	this->write_word(syscfg, this->base + ONENAND_REG_SYS_CFG1);

	this->wait = onenand_try_interrupt_wait;
}