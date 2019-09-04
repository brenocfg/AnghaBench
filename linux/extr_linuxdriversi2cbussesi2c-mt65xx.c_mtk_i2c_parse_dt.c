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
struct mtk_i2c {scalar_t__ speed_hz; scalar_t__ clk_src_div; void* use_push_pull; void* have_pmic; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ I2C_DEFAULT_SPEED ; 
 void* of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 

__attribute__((used)) static int mtk_i2c_parse_dt(struct device_node *np, struct mtk_i2c *i2c)
{
	int ret;

	ret = of_property_read_u32(np, "clock-frequency", &i2c->speed_hz);
	if (ret < 0)
		i2c->speed_hz = I2C_DEFAULT_SPEED;

	ret = of_property_read_u32(np, "clock-div", &i2c->clk_src_div);
	if (ret < 0)
		return ret;

	if (i2c->clk_src_div == 0)
		return -EINVAL;

	i2c->have_pmic = of_property_read_bool(np, "mediatek,have-pmic");
	i2c->use_push_pull =
		of_property_read_bool(np, "mediatek,use-push-pull");

	return 0;
}