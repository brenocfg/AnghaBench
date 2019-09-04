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
typedef  int u8 ;
struct zx_hdmi {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int INTR1_MONITOR_DETECT ; 
 int /*<<< orphan*/  INTR1_STAT ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  L1_INTR_STAT ; 
 int L1_INTR_STAT_INTR1 ; 
 int hdmi_readb (struct zx_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_writeb (struct zx_hdmi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t zx_hdmi_irq_handler(int irq, void *dev_id)
{
	struct zx_hdmi *hdmi = dev_id;
	u8 lstat;

	lstat = hdmi_readb(hdmi, L1_INTR_STAT);

	/* Monitor detect/HPD interrupt */
	if (lstat & L1_INTR_STAT_INTR1) {
		u8 stat;

		stat = hdmi_readb(hdmi, INTR1_STAT);
		hdmi_writeb(hdmi, INTR1_STAT, stat);

		if (stat & INTR1_MONITOR_DETECT)
			return IRQ_WAKE_THREAD;
	}

	return IRQ_NONE;
}