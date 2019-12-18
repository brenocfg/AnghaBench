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

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int open_sysfs (char const*,char const*,int /*<<< orphan*/ ) ; 
 int read_sysfs_int_fd (int,char const*,char const*) ; 

int read_sysfs_int(const char *sys_pfx, const char *node)
{
	int fd, val;

	fd = open_sysfs(sys_pfx, node, O_RDONLY);
	val = read_sysfs_int_fd(fd, sys_pfx, node);
	close(fd);
	return val;
}