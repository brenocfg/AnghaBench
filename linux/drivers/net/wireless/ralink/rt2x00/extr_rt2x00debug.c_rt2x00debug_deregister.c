#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct rt2x00debug_intf* data; } ;
struct TYPE_3__ {struct rt2x00debug_intf* data; } ;
struct rt2x00debug_intf {TYPE_2__ driver_blob; TYPE_1__ chipset_blob; int /*<<< orphan*/  driver_folder; int /*<<< orphan*/  frame_dump_skbqueue; } ;
struct rt2x00_dev {struct rt2x00debug_intf* debugfs_intf; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rt2x00debug_intf*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void rt2x00debug_deregister(struct rt2x00_dev *rt2x00dev)
{
	struct rt2x00debug_intf *intf = rt2x00dev->debugfs_intf;

	if (unlikely(!intf))
		return;

	skb_queue_purge(&intf->frame_dump_skbqueue);

	debugfs_remove_recursive(intf->driver_folder);
	kfree(intf->chipset_blob.data);
	kfree(intf->driver_blob.data);
	kfree(intf);

	rt2x00dev->debugfs_intf = NULL;
}