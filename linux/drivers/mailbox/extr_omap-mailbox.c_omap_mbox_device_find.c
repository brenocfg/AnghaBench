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
struct omap_mbox_device {struct omap_mbox** mboxes; } ;
struct omap_mbox {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct omap_mbox *omap_mbox_device_find(struct omap_mbox_device *mdev,
					       const char *mbox_name)
{
	struct omap_mbox *_mbox, *mbox = NULL;
	struct omap_mbox **mboxes = mdev->mboxes;
	int i;

	if (!mboxes)
		return NULL;

	for (i = 0; (_mbox = mboxes[i]); i++) {
		if (!strcmp(_mbox->name, mbox_name)) {
			mbox = _mbox;
			break;
		}
	}
	return mbox;
}