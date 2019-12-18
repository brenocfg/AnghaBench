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
struct rt2880_priv {TYPE_1__** func; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */
 struct rt2880_priv* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static const char *rt2880_pmx_func_name(struct pinctrl_dev *pctrldev,
					unsigned int func)
{
	struct rt2880_priv *p = pinctrl_dev_get_drvdata(pctrldev);

	return p->func[func]->name;
}