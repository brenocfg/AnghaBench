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
 scalar_t__ CM_FAIL ; 
 int /*<<< orphan*/  DMERR (char*,char const*) ; 
 int /*<<< orphan*/  DMINFO (char*,char const*) ; 
 int /*<<< orphan*/  __set_clone_mode (struct clone*,scalar_t__) ; 
 char* clone_device_name (struct clone*) ; 
 scalar_t__ dm_clone_reload_in_core_bitset (int /*<<< orphan*/ ) ; 
 scalar_t__ get_clone_mode (struct clone*) ; 

__attribute__((used)) static void __reload_in_core_bitset(struct clone *clone)
{
	const char *dev_name = clone_device_name(clone);

	if (get_clone_mode(clone) == CM_FAIL)
		return;

	/* Reload the on-disk bitset */
	DMINFO("%s: Reloading on-disk bitmap", dev_name);
	if (dm_clone_reload_in_core_bitset(clone->cmd)) {
		DMERR("%s: Failed to reload on-disk bitmap", dev_name);
		__set_clone_mode(clone, CM_FAIL);
	}
}