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
struct u300_pmx {int dummy; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 struct u300_pmx* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  u300_pmx_endisable (struct u300_pmx*,unsigned int,int) ; 

__attribute__((used)) static int u300_pmx_set_mux(struct pinctrl_dev *pctldev, unsigned selector,
			    unsigned group)
{
	struct u300_pmx *upmx;

	/* There is nothing to do with the power pins */
	if (selector == 0)
		return 0;

	upmx = pinctrl_dev_get_drvdata(pctldev);
	u300_pmx_endisable(upmx, selector, true);

	return 0;
}