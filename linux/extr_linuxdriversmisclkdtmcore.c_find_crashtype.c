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
struct crashtype {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct crashtype const*) ; 
 struct crashtype const* crashtypes ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct crashtype *find_crashtype(const char *name)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(crashtypes); i++) {
		if (!strcmp(name, crashtypes[i].name))
			return &crashtypes[i];
	}

	return NULL;
}