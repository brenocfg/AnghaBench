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
 int /*<<< orphan*/  DMWARN (char*) ; 
 int /*<<< orphan*/  _transient_compat_type ; 
 int /*<<< orphan*/  _transient_type ; 
 int dm_exception_store_type_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_exception_store_type_unregister (int /*<<< orphan*/ *) ; 

int dm_transient_snapshot_init(void)
{
	int r;

	r = dm_exception_store_type_register(&_transient_type);
	if (r) {
		DMWARN("Unable to register transient exception store type");
		return r;
	}

	r = dm_exception_store_type_register(&_transient_compat_type);
	if (r) {
		DMWARN("Unable to register old-style transient "
		       "exception store type");
		dm_exception_store_type_unregister(&_transient_type);
		return r;
	}

	return r;
}