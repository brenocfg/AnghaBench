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
struct rtc_wkalrm {int enabled; int pending; int /*<<< orphan*/  time; } ;
struct imxdi_dev {int /*<<< orphan*/  write_mutex; scalar_t__ ioaddr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DCAMR ; 
 scalar_t__ DIER ; 
 int DIER_CAIE ; 
 scalar_t__ DSR ; 
 int DSR_CAF ; 
 struct imxdi_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dryice_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct imxdi_dev *imxdi = dev_get_drvdata(dev);
	u32 dcamr;

	dcamr = readl(imxdi->ioaddr + DCAMR);
	rtc_time64_to_tm(dcamr, &alarm->time);

	/* alarm is enabled if the interrupt is enabled */
	alarm->enabled = (readl(imxdi->ioaddr + DIER) & DIER_CAIE) != 0;

	/* don't allow the DSR read to mess up DSR_WCF */
	mutex_lock(&imxdi->write_mutex);

	/* alarm is pending if the alarm flag is set */
	alarm->pending = (readl(imxdi->ioaddr + DSR) & DSR_CAF) != 0;

	mutex_unlock(&imxdi->write_mutex);

	return 0;
}