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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  domain; } ;
struct mdp5_mdss {TYPE_1__ irqcontroller; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REG_MDSS_HW_INTR_STATUS ; 
 int /*<<< orphan*/  VERB (char*,int) ; 
 int fls (int) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int mdss_read (struct mdp5_mdss*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t mdss_irq(int irq, void *arg)
{
	struct mdp5_mdss *mdp5_mdss = arg;
	u32 intr;

	intr = mdss_read(mdp5_mdss, REG_MDSS_HW_INTR_STATUS);

	VERB("intr=%08x", intr);

	while (intr) {
		irq_hw_number_t hwirq = fls(intr) - 1;

		generic_handle_irq(irq_find_mapping(
				mdp5_mdss->irqcontroller.domain, hwirq));
		intr &= ~(1 << hwirq);
	}

	return IRQ_HANDLED;
}