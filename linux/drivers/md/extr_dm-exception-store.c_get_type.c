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
struct dm_exception_store_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,char const*) ; 
 int /*<<< orphan*/  DMWARN (char*,char const*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dm_exception_store_type* _get_exception_store_type (char const*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ request_module (char*,char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static struct dm_exception_store_type *get_type(const char *type_name)
{
	char *p, *type_name_dup;
	struct dm_exception_store_type *type;

	type = _get_exception_store_type(type_name);
	if (type)
		return type;

	type_name_dup = kstrdup(type_name, GFP_KERNEL);
	if (!type_name_dup) {
		DMERR("No memory left to attempt load for \"%s\"", type_name);
		return NULL;
	}

	while (request_module("dm-exstore-%s", type_name_dup) ||
	       !(type = _get_exception_store_type(type_name))) {
		p = strrchr(type_name_dup, '-');
		if (!p)
			break;
		p[0] = '\0';
	}

	if (!type)
		DMWARN("Module for exstore type \"%s\" not found.", type_name);

	kfree(type_name_dup);

	return type;
}