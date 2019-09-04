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
struct target_type {int dummy; } ;

/* Variables and functions */
 struct target_type* get_target_type (char const*) ; 
 int /*<<< orphan*/  load_module (char const*) ; 

struct target_type *dm_get_target_type(const char *name)
{
	struct target_type *tt = get_target_type(name);

	if (!tt) {
		load_module(name);
		tt = get_target_type(name);
	}

	return tt;
}