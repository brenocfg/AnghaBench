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
struct mtk_cec {int hpd; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int) ; 
 struct mtk_cec* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mtk_cec_clear_htplg_irq (struct mtk_cec*) ; 
 int /*<<< orphan*/  mtk_cec_hpd_event (struct mtk_cec*,int) ; 
 int mtk_cec_hpd_high (struct device*) ; 

__attribute__((used)) static irqreturn_t mtk_cec_htplg_isr_thread(int irq, void *arg)
{
	struct device *dev = arg;
	struct mtk_cec *cec = dev_get_drvdata(dev);
	bool hpd;

	mtk_cec_clear_htplg_irq(cec);
	hpd = mtk_cec_hpd_high(dev);

	if (cec->hpd != hpd) {
		dev_dbg(dev, "hotplug event! cur hpd = %d, hpd = %d\n",
			cec->hpd, hpd);
		cec->hpd = hpd;
		mtk_cec_hpd_event(cec, hpd);
	}
	return IRQ_HANDLED;
}