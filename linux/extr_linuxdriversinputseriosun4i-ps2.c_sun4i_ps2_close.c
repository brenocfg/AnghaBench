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
struct sun4i_ps2data {int /*<<< orphan*/  irq; scalar_t__ reg_base; } ;
struct serio {struct sun4i_ps2data* port_data; } ;

/* Variables and functions */
 int PS2_GCTL_INTEN ; 
 scalar_t__ PS2_REG_GCTL ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void sun4i_ps2_close(struct serio *serio)
{
	struct sun4i_ps2data *drvdata = serio->port_data;
	u32 rval;

	/* Shut off the interrupt */
	rval = readl(drvdata->reg_base + PS2_REG_GCTL);
	writel(rval & ~(PS2_GCTL_INTEN), drvdata->reg_base + PS2_REG_GCTL);

	synchronize_irq(drvdata->irq);
}