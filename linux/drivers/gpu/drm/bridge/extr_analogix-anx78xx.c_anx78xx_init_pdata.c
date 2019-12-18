#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct anx78xx_platform_data {void* gpiod_reset; void* gpiod_pd; void* gpiod_hpd; void* dvdd10; } ;
struct anx78xx {TYPE_1__* client; struct anx78xx_platform_data pdata; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int PTR_ERR_OR_ZERO (void*) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get (struct device*,char*) ; 

__attribute__((used)) static int anx78xx_init_pdata(struct anx78xx *anx78xx)
{
	struct anx78xx_platform_data *pdata = &anx78xx->pdata;
	struct device *dev = &anx78xx->client->dev;

	/* 1.0V digital core power regulator  */
	pdata->dvdd10 = devm_regulator_get(dev, "dvdd10");
	if (IS_ERR(pdata->dvdd10)) {
		DRM_ERROR("DVDD10 regulator not found\n");
		return PTR_ERR(pdata->dvdd10);
	}

	/* GPIO for HPD */
	pdata->gpiod_hpd = devm_gpiod_get(dev, "hpd", GPIOD_IN);
	if (IS_ERR(pdata->gpiod_hpd))
		return PTR_ERR(pdata->gpiod_hpd);

	/* GPIO for chip power down */
	pdata->gpiod_pd = devm_gpiod_get(dev, "pd", GPIOD_OUT_HIGH);
	if (IS_ERR(pdata->gpiod_pd))
		return PTR_ERR(pdata->gpiod_pd);

	/* GPIO for chip reset */
	pdata->gpiod_reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);

	return PTR_ERR_OR_ZERO(pdata->gpiod_reset);
}