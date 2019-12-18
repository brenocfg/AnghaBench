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
typedef  int u32 ;
struct brcmstb_i2c_dev {TYPE_1__* bsc_regmap; } ;
struct TYPE_2__ {int iic_enable; } ;

/* Variables and functions */
 int COND_START_STOP ; 

__attribute__((used)) static void brcmstb_set_i2c_start_stop(struct brcmstb_i2c_dev *dev,
				       u32 cond_flag)
{
	u32 regval = dev->bsc_regmap->iic_enable;

	dev->bsc_regmap->iic_enable = (regval & ~COND_START_STOP) | cond_flag;
}