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
struct rtc_wkalrm {scalar_t__ enabled; int /*<<< orphan*/  time; } ;
struct imxdi_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCAMR ; 
 int /*<<< orphan*/  DIER_CAIE ; 
 struct imxdi_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  di_int_disable (struct imxdi_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  di_int_enable (struct imxdi_dev*,int /*<<< orphan*/ ) ; 
 int di_write_wait (struct imxdi_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_tm_to_time64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dryice_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct imxdi_dev *imxdi = dev_get_drvdata(dev);
	int rc;

	/* write the new alarm time */
	rc = di_write_wait(imxdi, rtc_tm_to_time64(&alarm->time), DCAMR);
	if (rc)
		return rc;

	if (alarm->enabled)
		di_int_enable(imxdi, DIER_CAIE);  /* enable alarm intr */
	else
		di_int_disable(imxdi, DIER_CAIE); /* disable alarm intr */

	return 0;
}