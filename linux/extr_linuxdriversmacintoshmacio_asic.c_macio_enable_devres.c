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
struct macio_devres {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct macio_dev {TYPE_1__ ofdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct macio_devres* devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct macio_devres* devres_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devres_get (int /*<<< orphan*/ *,struct macio_devres*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  maciom_release ; 

int macio_enable_devres(struct macio_dev *dev)
{
	struct macio_devres *dr;

	dr = devres_find(&dev->ofdev.dev, maciom_release, NULL, NULL);
	if (!dr) {
		dr = devres_alloc(maciom_release, sizeof(*dr), GFP_KERNEL);
		if (!dr)
			return -ENOMEM;
	}
	return devres_get(&dev->ofdev.dev, dr, NULL, NULL) != NULL;
}