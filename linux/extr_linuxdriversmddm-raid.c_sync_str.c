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
typedef  enum sync_state { ____Placeholder_sync_state } sync_state ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (char const**) ; 
 scalar_t__ __within_range (int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static const char *sync_str(enum sync_state state)
{
	/* Has to be in above sync_state order! */
	static const char *sync_strs[] = {
		"frozen",
		"reshape",
		"resync",
		"check",
		"repair",
		"recover",
		"idle"
	};

	return __within_range(state, 0, ARRAY_SIZE(sync_strs) - 1) ? sync_strs[state] : "undef";
}