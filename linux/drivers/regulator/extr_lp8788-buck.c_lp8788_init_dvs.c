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
typedef  int /*<<< orphan*/  u8 ;
struct platform_device {int dummy; } ;
struct lp8788_platform_data {int /*<<< orphan*/  buck2_dvs; int /*<<< orphan*/  buck1_dvs; } ;
struct lp8788_buck {TYPE_1__* lp; } ;
typedef  enum lp8788_buck_id { ____Placeholder_lp8788_buck_id } lp8788_buck_id ;
struct TYPE_2__ {struct lp8788_platform_data* pdata; } ;

/* Variables and functions */
 int BUCK1 ; 
 int BUCK2 ; 
 int /*<<< orphan*/  LP8788_BUCK1_DVS_I2C ; 
 int /*<<< orphan*/  LP8788_BUCK1_DVS_PIN ; 
 int /*<<< orphan*/  LP8788_BUCK1_DVS_SEL_M ; 
 int /*<<< orphan*/  LP8788_BUCK2_DVS_I2C ; 
 int /*<<< orphan*/  LP8788_BUCK2_DVS_PIN ; 
 int /*<<< orphan*/  LP8788_BUCK2_DVS_SEL_M ; 
 int /*<<< orphan*/  LP8788_BUCK_DVS_SEL ; 
 scalar_t__ lp8788_dvs_gpio_request (struct platform_device*,struct lp8788_buck*,int) ; 
 int lp8788_update_bits (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp8788_init_dvs(struct platform_device *pdev,
			struct lp8788_buck *buck, enum lp8788_buck_id id)
{
	struct lp8788_platform_data *pdata = buck->lp->pdata;
	u8 mask[] = { LP8788_BUCK1_DVS_SEL_M, LP8788_BUCK2_DVS_SEL_M };
	u8 val[]  = { LP8788_BUCK1_DVS_PIN, LP8788_BUCK2_DVS_PIN };
	u8 default_dvs_mode[] = { LP8788_BUCK1_DVS_I2C, LP8788_BUCK2_DVS_I2C };

	/* no dvs for buck3, 4 */
	if (id > BUCK2)
		return 0;

	/* no dvs platform data, then dvs will be selected by I2C registers */
	if (!pdata)
		goto set_default_dvs_mode;

	if ((id == BUCK1 && !pdata->buck1_dvs) ||
		(id == BUCK2 && !pdata->buck2_dvs))
		goto set_default_dvs_mode;

	if (lp8788_dvs_gpio_request(pdev, buck, id))
		goto set_default_dvs_mode;

	return lp8788_update_bits(buck->lp, LP8788_BUCK_DVS_SEL, mask[id],
				val[id]);

set_default_dvs_mode:
	return lp8788_update_bits(buck->lp, LP8788_BUCK_DVS_SEL, mask[id],
				  default_dvs_mode[id]);
}