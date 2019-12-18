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
struct mapped_device {int dummy; } ;
struct dm_uevent {struct mapped_device* md; int /*<<< orphan*/  elist; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _dm_event_cache ; 
 struct dm_uevent* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dm_uevent *dm_uevent_alloc(struct mapped_device *md)
{
	struct dm_uevent *event;

	event = kmem_cache_zalloc(_dm_event_cache, GFP_ATOMIC);
	if (!event)
		return NULL;

	INIT_LIST_HEAD(&event->elist);
	event->md = md;

	return event;
}