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
 int /*<<< orphan*/  DMERR (char*) ; 
 int dm_persistent_snapshot_init () ; 
 int /*<<< orphan*/  dm_transient_snapshot_exit () ; 
 int dm_transient_snapshot_init () ; 

int dm_exception_store_init(void)
{
	int r;

	r = dm_transient_snapshot_init();
	if (r) {
		DMERR("Unable to register transient exception store type.");
		goto transient_fail;
	}

	r = dm_persistent_snapshot_init();
	if (r) {
		DMERR("Unable to register persistent exception store type");
		goto persistent_fail;
	}

	return 0;

persistent_fail:
	dm_transient_snapshot_exit();
transient_fail:
	return r;
}