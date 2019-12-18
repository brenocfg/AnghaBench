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
 int /*<<< orphan*/  _transient_compat_type ; 
 int /*<<< orphan*/  _transient_type ; 
 int /*<<< orphan*/  dm_exception_store_type_unregister (int /*<<< orphan*/ *) ; 

void dm_transient_snapshot_exit(void)
{
	dm_exception_store_type_unregister(&_transient_type);
	dm_exception_store_type_unregister(&_transient_compat_type);
}