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
struct elevator_type {scalar_t__ elevator_alias; scalar_t__ elevator_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static bool elevator_match(const struct elevator_type *e, const char *name)
{
	if (!strcmp(e->elevator_name, name))
		return true;
	if (e->elevator_alias && !strcmp(e->elevator_alias, name))
		return true;

	return false;
}