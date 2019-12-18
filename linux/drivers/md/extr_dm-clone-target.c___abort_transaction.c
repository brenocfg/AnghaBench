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
struct clone {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_FAIL ; 
 scalar_t__ CM_READ_ONLY ; 
 int /*<<< orphan*/  DMERR (char*,char const*) ; 
 int /*<<< orphan*/  __set_clone_mode (struct clone*,int /*<<< orphan*/ ) ; 
 char* clone_device_name (struct clone*) ; 
 scalar_t__ dm_clone_metadata_abort (int /*<<< orphan*/ ) ; 
 scalar_t__ get_clone_mode (struct clone*) ; 

__attribute__((used)) static void __abort_transaction(struct clone *clone)
{
	const char *dev_name = clone_device_name(clone);

	if (get_clone_mode(clone) >= CM_READ_ONLY)
		return;

	DMERR("%s: Aborting current metadata transaction", dev_name);
	if (dm_clone_metadata_abort(clone->cmd)) {
		DMERR("%s: Failed to abort metadata transaction", dev_name);
		__set_clone_mode(clone, CM_FAIL);
	}
}