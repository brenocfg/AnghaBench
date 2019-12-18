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
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct dc_pinmap {scalar_t__ regs; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dc_client_sel (unsigned int,int*,int*) ; 
 struct dc_pinmap* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int readb_relaxed (scalar_t__) ; 

__attribute__((used)) static int dc_pmx_request_gpio(struct pinctrl_dev *pcdev,
			       struct pinctrl_gpio_range *range,
			       unsigned offset)
{
	struct dc_pinmap *pmap = pinctrl_dev_get_drvdata(pcdev);
	int bit_off, reg_off;
	u8 reg;

	dc_client_sel(offset, &reg_off, &bit_off);

	reg = readb_relaxed(pmap->regs + reg_off);
	if ((reg & (3 << bit_off)) != 0)
		return -EBUSY;

	return 0;
}