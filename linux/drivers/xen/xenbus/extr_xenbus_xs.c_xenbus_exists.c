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
 scalar_t__ IS_ERR (char**) ; 
 int /*<<< orphan*/  kfree (char**) ; 
 char** xenbus_directory (struct xenbus_transaction,char const*,char const*,int*) ; 

int xenbus_exists(struct xenbus_transaction t,
		  const char *dir, const char *node)
{
	char **d;
	int dir_n;

	d = xenbus_directory(t, dir, node, &dir_n);
	if (IS_ERR(d))
		return 0;
	kfree(d);
	return 1;
}