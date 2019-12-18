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
 int PTR_ERR (char*) ; 
 int /*<<< orphan*/  XS_MKDIR ; 
 char* join (char const*,char const*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int xs_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_single (struct xenbus_transaction,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

int xenbus_mkdir(struct xenbus_transaction t,
		 const char *dir, const char *node)
{
	char *path;
	int ret;

	path = join(dir, node);
	if (IS_ERR(path))
		return PTR_ERR(path);

	ret = xs_error(xs_single(t, XS_MKDIR, path, NULL));
	kfree(path);
	return ret;
}