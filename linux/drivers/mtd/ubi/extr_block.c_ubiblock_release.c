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
struct ubiblock {scalar_t__ refcnt; int /*<<< orphan*/  dev_mutex; int /*<<< orphan*/ * desc; } ;
struct gendisk {struct ubiblock* private_data; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_close_volume (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ubiblock_release(struct gendisk *gd, fmode_t mode)
{
	struct ubiblock *dev = gd->private_data;

	mutex_lock(&dev->dev_mutex);
	dev->refcnt--;
	if (dev->refcnt == 0) {
		ubi_close_volume(dev->desc);
		dev->desc = NULL;
	}
	mutex_unlock(&dev->dev_mutex);
}