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
struct pinctrl {int /*<<< orphan*/  users; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct pinctrl* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 struct pinctrl* create_pinctrl (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct pinctrl* find_pinctrl (struct device*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 

struct pinctrl *pinctrl_get(struct device *dev)
{
	struct pinctrl *p;

	if (WARN_ON(!dev))
		return ERR_PTR(-EINVAL);

	/*
	 * See if somebody else (such as the device core) has already
	 * obtained a handle to the pinctrl for this device. In that case,
	 * return another pointer to it.
	 */
	p = find_pinctrl(dev);
	if (p) {
		dev_dbg(dev, "obtain a copy of previously claimed pinctrl\n");
		kref_get(&p->users);
		return p;
	}

	return create_pinctrl(dev, NULL);
}