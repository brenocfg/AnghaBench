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
struct tda18271_config {scalar_t__ rf_cal_on_startup; } ;

/* Variables and functions */
 int tda18271_cal_on_startup ; 

__attribute__((used)) static inline int tda18271_need_cal_on_startup(struct tda18271_config *cfg)
{
	/* tda18271_cal_on_startup == -1 when cal module option is unset */
	return ((tda18271_cal_on_startup == -1) ?
		/* honor configuration setting */
		((cfg) && (cfg->rf_cal_on_startup)) :
		/* module option overrides configuration setting */
		(tda18271_cal_on_startup)) ? 1 : 0;
}