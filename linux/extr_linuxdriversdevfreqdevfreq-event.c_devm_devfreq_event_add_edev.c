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
struct device {int dummy; } ;
struct devfreq_event_dev {int dummy; } ;
struct devfreq_event_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct devfreq_event_dev* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct devfreq_event_dev*) ; 
 struct devfreq_event_dev* devfreq_event_add_edev (struct device*,struct devfreq_event_desc*) ; 
 int /*<<< orphan*/  devm_devfreq_event_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct devfreq_event_dev**) ; 
 struct devfreq_event_dev** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct devfreq_event_dev**) ; 

struct devfreq_event_dev *devm_devfreq_event_add_edev(struct device *dev,
						struct devfreq_event_desc *desc)
{
	struct devfreq_event_dev **ptr, *edev;

	ptr = devres_alloc(devm_devfreq_event_release, sizeof(*ptr),
				GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	edev = devfreq_event_add_edev(dev, desc);
	if (IS_ERR(edev)) {
		devres_free(ptr);
		return ERR_PTR(-ENOMEM);
	}

	*ptr = edev;
	devres_add(dev, ptr);

	return edev;
}