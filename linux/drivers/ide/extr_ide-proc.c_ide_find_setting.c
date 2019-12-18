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
struct ide_proc_devset {scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ strcmp (scalar_t__,char*) ; 

__attribute__((used)) static
const struct ide_proc_devset *ide_find_setting(const struct ide_proc_devset *st,
					       char *name)
{
	while (st->name) {
		if (strcmp(st->name, name) == 0)
			break;
		st++;
	}
	return st->name ? st : NULL;
}