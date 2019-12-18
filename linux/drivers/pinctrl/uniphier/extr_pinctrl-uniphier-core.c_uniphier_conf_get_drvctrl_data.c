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
struct pinctrl_dev {int dummy; } ;
struct pin_desc {int /*<<< orphan*/  drv_data; } ;
typedef  enum uniphier_pin_drv_type { ____Placeholder_uniphier_pin_drv_type } uniphier_pin_drv_type ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int UNIPHIER_PINCTRL_DRV2CTRL_BASE ; 
 unsigned int UNIPHIER_PINCTRL_DRV3CTRL_BASE ; 
 unsigned int UNIPHIER_PINCTRL_DRVCTRL_BASE ; 
#define  UNIPHIER_PIN_DRV_1BIT 133 
#define  UNIPHIER_PIN_DRV_2BIT 132 
#define  UNIPHIER_PIN_DRV_3BIT 131 
#define  UNIPHIER_PIN_DRV_FIXED4 130 
#define  UNIPHIER_PIN_DRV_FIXED5 129 
#define  UNIPHIER_PIN_DRV_FIXED8 128 
 struct pin_desc* pin_desc_get (struct pinctrl_dev*,unsigned int) ; 
 unsigned int* uniphier_conf_drv_strengths_1bit ; 
 unsigned int* uniphier_conf_drv_strengths_2bit ; 
 unsigned int* uniphier_conf_drv_strengths_3bit ; 
 unsigned int* uniphier_conf_drv_strengths_fixed4 ; 
 unsigned int* uniphier_conf_drv_strengths_fixed5 ; 
 unsigned int* uniphier_conf_drv_strengths_fixed8 ; 
 int uniphier_pin_get_drv_type (int /*<<< orphan*/ ) ; 
 unsigned int uniphier_pin_get_drvctrl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uniphier_conf_get_drvctrl_data(struct pinctrl_dev *pctldev,
					  unsigned int pin, unsigned int *reg,
					  unsigned int *shift,
					  unsigned int *mask,
					  const unsigned int **strengths)
{
	const struct pin_desc *desc = pin_desc_get(pctldev, pin);
	enum uniphier_pin_drv_type type =
				uniphier_pin_get_drv_type(desc->drv_data);
	unsigned int base = 0;
	unsigned int stride = 0;
	unsigned int width = 0;
	unsigned int drvctrl;

	switch (type) {
	case UNIPHIER_PIN_DRV_1BIT:
		*strengths = uniphier_conf_drv_strengths_1bit;
		base = UNIPHIER_PINCTRL_DRVCTRL_BASE;
		stride = 1;
		width = 1;
		break;
	case UNIPHIER_PIN_DRV_2BIT:
		*strengths = uniphier_conf_drv_strengths_2bit;
		base = UNIPHIER_PINCTRL_DRV2CTRL_BASE;
		stride = 2;
		width = 2;
		break;
	case UNIPHIER_PIN_DRV_3BIT:
		*strengths = uniphier_conf_drv_strengths_3bit;
		base = UNIPHIER_PINCTRL_DRV3CTRL_BASE;
		stride = 4;
		width = 3;
		break;
	case UNIPHIER_PIN_DRV_FIXED4:
		*strengths = uniphier_conf_drv_strengths_fixed4;
		break;
	case UNIPHIER_PIN_DRV_FIXED5:
		*strengths = uniphier_conf_drv_strengths_fixed5;
		break;
	case UNIPHIER_PIN_DRV_FIXED8:
		*strengths = uniphier_conf_drv_strengths_fixed8;
		break;
	default:
		/* drive strength control is not supported for this pin */
		return -EINVAL;
	}

	drvctrl = uniphier_pin_get_drvctrl(desc->drv_data);
	drvctrl *= stride;

	*reg = base + drvctrl / 32 * 4;
	*shift = drvctrl % 32;
	*mask = (1U << width) - 1;

	return 0;
}