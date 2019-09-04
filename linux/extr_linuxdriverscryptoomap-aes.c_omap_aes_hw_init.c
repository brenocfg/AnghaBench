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
struct omap_aes_dev {int flags; int /*<<< orphan*/  dev; scalar_t__ err; } ;

/* Variables and functions */
 int FLAGS_INIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_aes_hw_init(struct omap_aes_dev *dd)
{
	int err;

	if (!(dd->flags & FLAGS_INIT)) {
		dd->flags |= FLAGS_INIT;
		dd->err = 0;
	}

	err = pm_runtime_get_sync(dd->dev);
	if (err < 0) {
		dev_err(dd->dev, "failed to get sync: %d\n", err);
		return err;
	}

	return 0;
}