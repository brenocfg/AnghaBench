#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * priv_data; } ;
struct saa7134_dev {int has_remote; int /*<<< orphan*/  name; TYPE_3__* remote; TYPE_2__* mops; TYPE_1__ dmasound; scalar_t__ insuspend; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int mask_keydown; int mask_keyup; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* irq_ts_done ) (struct saa7134_dev*,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  SAA7134_IRQ1 ; 
 int /*<<< orphan*/  SAA7134_IRQ2 ; 
 int /*<<< orphan*/  SAA7134_IRQ2_INTE_GPIO16_N ; 
 int /*<<< orphan*/  SAA7134_IRQ2_INTE_GPIO16_P ; 
 int /*<<< orphan*/  SAA7134_IRQ2_INTE_GPIO18_N ; 
 int /*<<< orphan*/  SAA7134_IRQ2_INTE_GPIO18_P ; 
 int /*<<< orphan*/  SAA7134_IRQ2_INTE_PE ; 
 int /*<<< orphan*/  SAA7134_IRQ_REPORT ; 
 unsigned long SAA7134_IRQ_REPORT_DONE_RA0 ; 
 unsigned long SAA7134_IRQ_REPORT_DONE_RA2 ; 
 unsigned long SAA7134_IRQ_REPORT_DONE_RA3 ; 
 unsigned long SAA7134_IRQ_REPORT_GPIO16 ; 
 unsigned long SAA7134_IRQ_REPORT_GPIO18 ; 
 unsigned long SAA7134_IRQ_REPORT_INTL ; 
 unsigned long SAA7134_IRQ_REPORT_PE ; 
 unsigned long SAA7134_IRQ_REPORT_RDCAP ; 
 int /*<<< orphan*/  SAA7134_IRQ_STATUS ; 
#define  SAA7134_REMOTE_GPIO 129 
#define  SAA7134_REMOTE_I2C 128 
 scalar_t__ card_has_mpeg (struct saa7134_dev*) ; 
 int /*<<< orphan*/  irq_dbg (int,char*) ; 
 scalar_t__ irq_debug ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_irqstatus (struct saa7134_dev*,int,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  saa7134_input_irq (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa7134_irq_ts_done (struct saa7134_dev*,unsigned long) ; 
 int /*<<< orphan*/  saa7134_irq_vbi_done (struct saa7134_dev*,unsigned long) ; 
 int /*<<< orphan*/  saa7134_irq_video_done (struct saa7134_dev*,unsigned long) ; 
 int /*<<< orphan*/  saa7134_irq_video_signalchange (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa_clearl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long saa_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa_writel (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct saa7134_dev*,unsigned long) ; 

__attribute__((used)) static irqreturn_t saa7134_irq(int irq, void *dev_id)
{
	struct saa7134_dev *dev = (struct saa7134_dev*) dev_id;
	unsigned long report,status;
	int loop, handled = 0;

	if (dev->insuspend)
		goto out;

	for (loop = 0; loop < 10; loop++) {
		report = saa_readl(SAA7134_IRQ_REPORT);
		status = saa_readl(SAA7134_IRQ_STATUS);

		/* If dmasound support is active and we get a sound report,
		 * mask out the report and let the saa7134-alsa module deal
		 * with it */
		if ((report & SAA7134_IRQ_REPORT_DONE_RA3) &&
			(dev->dmasound.priv_data != NULL) )
		{
			irq_dbg(2, "preserving DMA sound interrupt\n");
			report &= ~SAA7134_IRQ_REPORT_DONE_RA3;
		}

		if (0 == report) {
			irq_dbg(2, "no (more) work\n");
			goto out;
		}

		handled = 1;
		saa_writel(SAA7134_IRQ_REPORT,report);
		if (irq_debug)
			print_irqstatus(dev,loop,report,status);


		if ((report & SAA7134_IRQ_REPORT_RDCAP) ||
			(report & SAA7134_IRQ_REPORT_INTL))
				saa7134_irq_video_signalchange(dev);


		if ((report & SAA7134_IRQ_REPORT_DONE_RA0) &&
		    (status & 0x60) == 0)
			saa7134_irq_video_done(dev,status);

		if ((report & SAA7134_IRQ_REPORT_DONE_RA0) &&
		    (status & 0x40) == 0x40)
			saa7134_irq_vbi_done(dev,status);

		if ((report & SAA7134_IRQ_REPORT_DONE_RA2) &&
		    card_has_mpeg(dev)) {
			if (dev->mops->irq_ts_done != NULL)
				dev->mops->irq_ts_done(dev, status);
			else
				saa7134_irq_ts_done(dev, status);
		}

		if (report & SAA7134_IRQ_REPORT_GPIO16) {
			switch (dev->has_remote) {
				case SAA7134_REMOTE_GPIO:
					if (!dev->remote)
						break;
					if  (dev->remote->mask_keydown & 0x10000) {
						saa7134_input_irq(dev);
					}
					break;

				case SAA7134_REMOTE_I2C:
					break;			/* FIXME: invoke I2C get_key() */

				default:			/* GPIO16 not used by IR remote */
					break;
			}
		}

		if (report & SAA7134_IRQ_REPORT_GPIO18) {
			switch (dev->has_remote) {
				case SAA7134_REMOTE_GPIO:
					if (!dev->remote)
						break;
					if ((dev->remote->mask_keydown & 0x40000) ||
					    (dev->remote->mask_keyup & 0x40000)) {
						saa7134_input_irq(dev);
					}
					break;

				case SAA7134_REMOTE_I2C:
					break;			/* FIXME: invoke I2C get_key() */

				default:			/* GPIO18 not used by IR remote */
					break;
			}
		}
	}

	if (10 == loop) {
		print_irqstatus(dev,loop,report,status);
		if (report & SAA7134_IRQ_REPORT_PE) {
			/* disable all parity error */
			pr_warn("%s/irq: looping -- clearing PE (parity error!) enable bit\n",
				dev->name);
			saa_clearl(SAA7134_IRQ2,SAA7134_IRQ2_INTE_PE);
		} else if (report & SAA7134_IRQ_REPORT_GPIO16) {
			/* disable gpio16 IRQ */
			pr_warn("%s/irq: looping -- clearing GPIO16 enable bit\n",
				dev->name);
			saa_clearl(SAA7134_IRQ2, SAA7134_IRQ2_INTE_GPIO16_P);
			saa_clearl(SAA7134_IRQ2, SAA7134_IRQ2_INTE_GPIO16_N);
		} else if (report & SAA7134_IRQ_REPORT_GPIO18) {
			/* disable gpio18 IRQs */
			pr_warn("%s/irq: looping -- clearing GPIO18 enable bit\n",
				dev->name);
			saa_clearl(SAA7134_IRQ2, SAA7134_IRQ2_INTE_GPIO18_P);
			saa_clearl(SAA7134_IRQ2, SAA7134_IRQ2_INTE_GPIO18_N);
		} else {
			/* disable all irqs */
			pr_warn("%s/irq: looping -- clearing all enable bits\n",
				dev->name);
			saa_writel(SAA7134_IRQ1,0);
			saa_writel(SAA7134_IRQ2,0);
		}
	}

 out:
	return IRQ_RETVAL(handled);
}