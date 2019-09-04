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
struct lp8788_led_platform_data {int scale; int num; int iout_code; } ;
struct lp8788_led_config {int scale; int num; int iout; } ;
struct lp8788_led {int isink_num; int /*<<< orphan*/  lp; } ;

/* Variables and functions */
 int LP8788_ISINK_CTRL ; 
 int LP8788_ISINK_SCALE_OFFSET ; 
 struct lp8788_led_config default_led_config ; 
 int* lp8788_iout_addr ; 
 int* lp8788_iout_mask ; 
 int lp8788_update_bits (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int lp8788_led_init_device(struct lp8788_led *led,
				struct lp8788_led_platform_data *pdata)
{
	struct lp8788_led_config *cfg = &default_led_config;
	u8 addr, mask, val;
	int ret;

	if (pdata) {
		cfg->scale = pdata->scale;
		cfg->num = pdata->num;
		cfg->iout = pdata->iout_code;
	}

	led->isink_num = cfg->num;

	/* scale configuration */
	addr = LP8788_ISINK_CTRL;
	mask = 1 << (cfg->num + LP8788_ISINK_SCALE_OFFSET);
	val = cfg->scale << (cfg->num + LP8788_ISINK_SCALE_OFFSET);
	ret = lp8788_update_bits(led->lp, addr, mask, val);
	if (ret)
		return ret;

	/* current configuration */
	addr = lp8788_iout_addr[cfg->num];
	mask = lp8788_iout_mask[cfg->num];
	val = cfg->iout;

	return lp8788_update_bits(led->lp, addr, mask, val);
}