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
struct mtk_cec {void (* hpd_event ) (int,struct device*) ;int /*<<< orphan*/  lock; struct device* hdmi_dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct mtk_cec* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mtk_cec_set_hpd_event(struct device *dev,
			   void (*hpd_event)(bool hpd, struct device *dev),
			   struct device *hdmi_dev)
{
	struct mtk_cec *cec = dev_get_drvdata(dev);
	unsigned long flags;

	spin_lock_irqsave(&cec->lock, flags);
	cec->hdmi_dev = hdmi_dev;
	cec->hpd_event = hpd_event;
	spin_unlock_irqrestore(&cec->lock, flags);
}