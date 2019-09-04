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
struct TYPE_2__ {int mode; } ;
struct cache {TYPE_1__ features; int /*<<< orphan*/  cmd; } ;
typedef  enum cache_metadata_mode { ____Placeholder_cache_metadata_mode } cache_metadata_mode ;

/* Variables and functions */
#define  CM_FAIL 130 
#define  CM_READ_ONLY 129 
#define  CM_WRITE 128 
 int /*<<< orphan*/  DMERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_device_name (struct cache*) ; 
 scalar_t__ dm_cache_metadata_needs_check (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dm_cache_metadata_set_read_only (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_cache_metadata_set_read_write (int /*<<< orphan*/ ) ; 
 int get_cache_mode (struct cache*) ; 
 int /*<<< orphan*/  notify_mode_switch (struct cache*,int) ; 

__attribute__((used)) static void set_cache_mode(struct cache *cache, enum cache_metadata_mode new_mode)
{
	bool needs_check;
	enum cache_metadata_mode old_mode = get_cache_mode(cache);

	if (dm_cache_metadata_needs_check(cache->cmd, &needs_check)) {
		DMERR("%s: unable to read needs_check flag, setting failure mode.",
		      cache_device_name(cache));
		new_mode = CM_FAIL;
	}

	if (new_mode == CM_WRITE && needs_check) {
		DMERR("%s: unable to switch cache to write mode until repaired.",
		      cache_device_name(cache));
		if (old_mode != new_mode)
			new_mode = old_mode;
		else
			new_mode = CM_READ_ONLY;
	}

	/* Never move out of fail mode */
	if (old_mode == CM_FAIL)
		new_mode = CM_FAIL;

	switch (new_mode) {
	case CM_FAIL:
	case CM_READ_ONLY:
		dm_cache_metadata_set_read_only(cache->cmd);
		break;

	case CM_WRITE:
		dm_cache_metadata_set_read_write(cache->cmd);
		break;
	}

	cache->features.mode = new_mode;

	if (new_mode != old_mode)
		notify_mode_switch(cache, new_mode);
}