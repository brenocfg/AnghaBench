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
struct dm_uevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dm_event_cache ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct dm_uevent*) ; 

__attribute__((used)) static void dm_uevent_free(struct dm_uevent *event)
{
	kmem_cache_free(_dm_event_cache, event);
}