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
struct snvs_rtc_data {scalar_t__ offset; int /*<<< orphan*/  regmap; } ;
struct rtc_wkalrm {int pending; int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SNVS_LPSR ; 
 int SNVS_LPSR_LPTA ; 
 scalar_t__ SNVS_LPTAR ; 
 struct snvs_rtc_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snvs_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct snvs_rtc_data *data = dev_get_drvdata(dev);
	u32 lptar, lpsr;

	regmap_read(data->regmap, data->offset + SNVS_LPTAR, &lptar);
	rtc_time64_to_tm(lptar, &alrm->time);

	regmap_read(data->regmap, data->offset + SNVS_LPSR, &lpsr);
	alrm->pending = (lpsr & SNVS_LPSR_LPTA) ? 1 : 0;

	return 0;
}