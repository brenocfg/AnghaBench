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
struct inno_hdmi_phy {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int inno_read (struct inno_hdmi_phy*,int) ; 
 int /*<<< orphan*/  inno_write (struct inno_hdmi_phy*,int,int) ; 

__attribute__((used)) static irqreturn_t inno_hdmi_phy_rk3328_hardirq(int irq, void *dev_id)
{
	struct inno_hdmi_phy *inno = dev_id;
	int intr_stat1, intr_stat2, intr_stat3;

	intr_stat1 = inno_read(inno, 0x04);
	intr_stat2 = inno_read(inno, 0x06);
	intr_stat3 = inno_read(inno, 0x08);

	if (intr_stat1)
		inno_write(inno, 0x04, intr_stat1);
	if (intr_stat2)
		inno_write(inno, 0x06, intr_stat2);
	if (intr_stat3)
		inno_write(inno, 0x08, intr_stat3);

	if (intr_stat1 || intr_stat2 || intr_stat3)
		return IRQ_WAKE_THREAD;

	return IRQ_HANDLED;
}