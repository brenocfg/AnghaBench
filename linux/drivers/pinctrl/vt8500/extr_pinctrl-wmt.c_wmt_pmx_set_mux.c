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
typedef  int /*<<< orphan*/  u32 ;
struct wmt_pinctrl_data {TYPE_1__* pins; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 struct wmt_pinctrl_data* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int wmt_set_pinmux (struct wmt_pinctrl_data*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wmt_pmx_set_mux(struct pinctrl_dev *pctldev,
			   unsigned func_selector,
			   unsigned group_selector)
{
	struct wmt_pinctrl_data *data = pinctrl_dev_get_drvdata(pctldev);
	u32 pinnum = data->pins[group_selector].number;

	return wmt_set_pinmux(data, func_selector, pinnum);
}