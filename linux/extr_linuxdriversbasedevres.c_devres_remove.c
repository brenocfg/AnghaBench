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
struct TYPE_2__ {int /*<<< orphan*/  entry; } ;
struct devres {void* data; TYPE_1__ node; } ;
struct device {int /*<<< orphan*/  devres_lock; } ;
typedef  int /*<<< orphan*/  dr_release_t ;
typedef  int /*<<< orphan*/  dr_match_t ;

/* Variables and functions */
 int /*<<< orphan*/  devres_log (struct device*,TYPE_1__*,char*) ; 
 struct devres* find_dr (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void * devres_remove(struct device *dev, dr_release_t release,
		     dr_match_t match, void *match_data)
{
	struct devres *dr;
	unsigned long flags;

	spin_lock_irqsave(&dev->devres_lock, flags);
	dr = find_dr(dev, release, match, match_data);
	if (dr) {
		list_del_init(&dr->node.entry);
		devres_log(dev, &dr->node, "REM");
	}
	spin_unlock_irqrestore(&dev->devres_lock, flags);

	if (dr)
		return dr->data;
	return NULL;
}