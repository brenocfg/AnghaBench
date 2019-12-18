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

/* Variables and functions */
 int /*<<< orphan*/  DMINFO (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KMEM_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _dm_event_cache ; 
 int /*<<< orphan*/  dm_uevent ; 

int dm_uevent_init(void)
{
	_dm_event_cache = KMEM_CACHE(dm_uevent, 0);
	if (!_dm_event_cache)
		return -ENOMEM;

	DMINFO("version 1.0.3");

	return 0;
}