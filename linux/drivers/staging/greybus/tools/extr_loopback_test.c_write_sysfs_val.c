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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int SYSFS_MAX_INT ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int open_sysfs (char const*,char const*,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ write (int,char*,int) ; 

void write_sysfs_val(const char *sys_pfx, const char *node, int val)
{
	int fd, len;
	char buf[SYSFS_MAX_INT];

	fd = open_sysfs(sys_pfx, node, O_RDWR);
	len = snprintf(buf, sizeof(buf), "%d", val);
	if (write(fd, buf, len) < 0) {
		fprintf(stderr, "unable to write to %s%s %s\n", sys_pfx, node,
			strerror(errno));
		close(fd);
		abort();
	}
	close(fd);
}