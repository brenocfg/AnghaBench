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
struct rtc_time {int dummy; } ;
struct imxdi_dev {scalar_t__ ioaddr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DCR ; 
 int DCR_TCE ; 
 int DCR_TCHL ; 
 int DCR_TCSL ; 
 scalar_t__ DSR ; 
 int DSR_SVF ; 
 scalar_t__ DTCLR ; 
 scalar_t__ DTCMR ; 
 int EPERM ; 
 struct imxdi_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  di_what_is_to_be_done (struct imxdi_dev*,char*) ; 
 int di_write_wait (struct imxdi_dev*,int,scalar_t__) ; 
 int readl (scalar_t__) ; 
 int rtc_tm_to_time64 (struct rtc_time*) ; 

__attribute__((used)) static int dryice_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct imxdi_dev *imxdi = dev_get_drvdata(dev);
	u32 dcr, dsr;
	int rc;

	dcr = readl(imxdi->ioaddr + DCR);
	dsr = readl(imxdi->ioaddr + DSR);

	if (!(dcr & DCR_TCE) || (dsr & DSR_SVF)) {
		if (dcr & DCR_TCHL) {
			/* we are even more out of luck */
			di_what_is_to_be_done(imxdi, "battery");
			return -EPERM;
		}
		if ((dcr & DCR_TCSL) || (dsr & DSR_SVF)) {
			/* we are out of luck for now */
			di_what_is_to_be_done(imxdi, "main");
			return -EPERM;
		}
	}

	/* zero the fractional part first */
	rc = di_write_wait(imxdi, 0, DTCLR);
	if (rc != 0)
		return rc;

	rc = di_write_wait(imxdi, rtc_tm_to_time64(tm), DTCMR);
	if (rc != 0)
		return rc;

	return di_write_wait(imxdi, readl(imxdi->ioaddr + DCR) | DCR_TCE, DCR);
}