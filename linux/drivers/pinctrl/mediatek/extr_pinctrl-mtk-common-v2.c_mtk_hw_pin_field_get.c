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
struct mtk_pinctrl {int /*<<< orphan*/  dev; } ;
struct mtk_pin_field {int dummy; } ;
struct mtk_pin_desc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int PINCTRL_PIN_REG_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int mtk_hw_pin_field_lookup (struct mtk_pinctrl*,struct mtk_pin_desc const*,int,struct mtk_pin_field*) ; 

__attribute__((used)) static int mtk_hw_pin_field_get(struct mtk_pinctrl *hw,
				const struct mtk_pin_desc *desc,
				int field, struct mtk_pin_field *pfd)
{
	if (field < 0 || field >= PINCTRL_PIN_REG_MAX) {
		dev_err(hw->dev, "Invalid Field %d\n", field);
		return -EINVAL;
	}

	return mtk_hw_pin_field_lookup(hw, desc, field, pfd);
}