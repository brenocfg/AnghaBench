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
struct uml_stat {int /*<<< orphan*/  ust_mode; } ;

/* Variables and functions */
 int OS_TYPE_BLOCKDEV ; 
 int OS_TYPE_CHARDEV ; 
 int OS_TYPE_DIR ; 
 int OS_TYPE_FIFO ; 
 int OS_TYPE_FILE ; 
 int OS_TYPE_SOCK ; 
 int OS_TYPE_SYMLINK ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 int os_stat_file (char*,struct uml_stat*) ; 

int os_file_type(char *file)
{
	struct uml_stat buf;
	int err;

	err = os_stat_file(file, &buf);
	if (err < 0)
		return err;

	if (S_ISDIR(buf.ust_mode))
		return OS_TYPE_DIR;
	else if (S_ISLNK(buf.ust_mode))
		return OS_TYPE_SYMLINK;
	else if (S_ISCHR(buf.ust_mode))
		return OS_TYPE_CHARDEV;
	else if (S_ISBLK(buf.ust_mode))
		return OS_TYPE_BLOCKDEV;
	else if (S_ISFIFO(buf.ust_mode))
		return OS_TYPE_FIFO;
	else if (S_ISSOCK(buf.ust_mode))
		return OS_TYPE_SOCK;
	else return OS_TYPE_FILE;
}