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
 int /*<<< orphan*/  _persistent_compat_type ; 
 int /*<<< orphan*/  _persistent_type ; 
 int dm_exception_store_type_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_exception_store_type_unregister (int /*<<< orphan*/ *) ; 

int dm_persistent_snapshot_init(void)
{
	int r;

	r = dm_exception_store_type_register(&_persistent_type);
	if (r) {
		DMERR("Unable to register persistent exception store type");
		return r;
	}

	r = dm_exception_store_type_register(&_persistent_compat_type);
	if (r) {
		DMERR("Unable to register old-style persistent exception "
		      "store type");
		dm_exception_store_type_unregister(&_persistent_type);
		return r;
	}

	return r;
}