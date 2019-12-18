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

/* Variables and functions */
 int WMT_FSEL_COUNT ; 

__attribute__((used)) static int wmt_pmx_get_functions_count(struct pinctrl_dev *pctldev)
{
	return WMT_FSEL_COUNT;
}