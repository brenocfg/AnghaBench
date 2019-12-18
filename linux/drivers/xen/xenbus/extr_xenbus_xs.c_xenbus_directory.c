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
struct xenbus_transaction {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (char*) ; 
 int /*<<< orphan*/  XS_DIRECTORY ; 
 char* join (char const*,char const*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char** split (char*,unsigned int,unsigned int*) ; 
 char* xs_single (struct xenbus_transaction,int /*<<< orphan*/ ,char*,unsigned int*) ; 

char **xenbus_directory(struct xenbus_transaction t,
			const char *dir, const char *node, unsigned int *num)
{
	char *strings, *path;
	unsigned int len;

	path = join(dir, node);
	if (IS_ERR(path))
		return (char **)path;

	strings = xs_single(t, XS_DIRECTORY, path, &len);
	kfree(path);
	if (IS_ERR(strings))
		return (char **)strings;

	return split(strings, len, num);
}