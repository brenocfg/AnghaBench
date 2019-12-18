#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct ap_driver {int /*<<< orphan*/  (* remove ) (struct ap_device*) ;} ;
struct ap_device {struct ap_driver* drv; } ;
struct TYPE_6__ {int /*<<< orphan*/  list; } ;
struct TYPE_5__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ap_list_lock ; 
 int /*<<< orphan*/  ap_queue_prepare_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  ap_queue_remove (TYPE_1__*) ; 
 scalar_t__ is_card_dev (struct device*) ; 
 scalar_t__ is_queue_dev (struct device*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ap_device*) ; 
 TYPE_2__* to_ap_card (struct device*) ; 
 struct ap_device* to_ap_dev (struct device*) ; 
 TYPE_1__* to_ap_queue (struct device*) ; 

__attribute__((used)) static int ap_device_remove(struct device *dev)
{
	struct ap_device *ap_dev = to_ap_dev(dev);
	struct ap_driver *ap_drv = ap_dev->drv;

	/* prepare ap queue device removal */
	if (is_queue_dev(dev))
		ap_queue_prepare_remove(to_ap_queue(dev));

	/* driver's chance to clean up gracefully */
	if (ap_drv->remove)
		ap_drv->remove(ap_dev);

	/* now do the ap queue device remove */
	if (is_queue_dev(dev))
		ap_queue_remove(to_ap_queue(dev));

	/* Remove queue/card from list of active queues/cards */
	spin_lock_bh(&ap_list_lock);
	if (is_card_dev(dev))
		list_del_init(&to_ap_card(dev)->list);
	else
		list_del_init(&to_ap_queue(dev)->list);
	spin_unlock_bh(&ap_list_lock);

	return 0;
}