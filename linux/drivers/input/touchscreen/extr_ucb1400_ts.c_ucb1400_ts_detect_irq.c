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
struct ucb1400_ts {int /*<<< orphan*/  irq; int /*<<< orphan*/  ac97; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int HZ ; 
 int /*<<< orphan*/  NO_IRQ ; 
 int /*<<< orphan*/  UCB_ADC_CR ; 
 int /*<<< orphan*/  UCB_ADC_DATA ; 
 int UCB_ADC_DAT_VALID ; 
 int UCB_ADC_ENA ; 
 int UCB_ADC_START ; 
 int UCB_IE_ADC ; 
 int /*<<< orphan*/  UCB_IE_CLEAR ; 
 int /*<<< orphan*/  UCB_IE_FAL ; 
 int /*<<< orphan*/  UCB_IE_RIS ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int jiffies ; 
 int /*<<< orphan*/  probe_irq_off (unsigned long) ; 
 unsigned long probe_irq_on () ; 
 scalar_t__ time_after (int,unsigned long) ; 
 int ucb1400_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucb1400_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ucb1400_ts_detect_irq(struct ucb1400_ts *ucb,
					   struct platform_device *pdev)
{
	unsigned long mask, timeout;

	mask = probe_irq_on();

	/* Enable the ADC interrupt. */
	ucb1400_reg_write(ucb->ac97, UCB_IE_RIS, UCB_IE_ADC);
	ucb1400_reg_write(ucb->ac97, UCB_IE_FAL, UCB_IE_ADC);
	ucb1400_reg_write(ucb->ac97, UCB_IE_CLEAR, 0xffff);
	ucb1400_reg_write(ucb->ac97, UCB_IE_CLEAR, 0);

	/* Cause an ADC interrupt. */
	ucb1400_reg_write(ucb->ac97, UCB_ADC_CR, UCB_ADC_ENA);
	ucb1400_reg_write(ucb->ac97, UCB_ADC_CR, UCB_ADC_ENA | UCB_ADC_START);

	/* Wait for the conversion to complete. */
	timeout = jiffies + HZ/2;
	while (!(ucb1400_reg_read(ucb->ac97, UCB_ADC_DATA) &
						UCB_ADC_DAT_VALID)) {
		cpu_relax();
		if (time_after(jiffies, timeout)) {
			dev_err(&pdev->dev, "timed out in IRQ probe\n");
			probe_irq_off(mask);
			return -ENODEV;
		}
	}
	ucb1400_reg_write(ucb->ac97, UCB_ADC_CR, 0);

	/* Disable and clear interrupt. */
	ucb1400_reg_write(ucb->ac97, UCB_IE_RIS, 0);
	ucb1400_reg_write(ucb->ac97, UCB_IE_FAL, 0);
	ucb1400_reg_write(ucb->ac97, UCB_IE_CLEAR, 0xffff);
	ucb1400_reg_write(ucb->ac97, UCB_IE_CLEAR, 0);

	/* Read triggered interrupt. */
	ucb->irq = probe_irq_off(mask);
	if (ucb->irq < 0 || ucb->irq == NO_IRQ)
		return -ENODEV;

	return 0;
}