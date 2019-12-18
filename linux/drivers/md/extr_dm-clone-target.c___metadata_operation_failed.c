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
struct clone {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_READ_ONLY ; 
 int /*<<< orphan*/  DMERR (char*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  __abort_transaction (struct clone*) ; 
 int /*<<< orphan*/  __reload_in_core_bitset (struct clone*) ; 
 int /*<<< orphan*/  __set_clone_mode (struct clone*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clone_device_name (struct clone*) ; 

__attribute__((used)) static void __metadata_operation_failed(struct clone *clone, const char *op, int r)
{
	DMERR("%s: Metadata operation `%s' failed: error = %d",
	      clone_device_name(clone), op, r);

	__abort_transaction(clone);
	__set_clone_mode(clone, CM_READ_ONLY);

	/*
	 * dm_clone_reload_in_core_bitset() may run concurrently with either
	 * dm_clone_set_region_hydrated() or dm_clone_cond_set_range(), but
	 * it's safe as we have already set the metadata to read-only mode.
	 */
	__reload_in_core_bitset(clone);
}