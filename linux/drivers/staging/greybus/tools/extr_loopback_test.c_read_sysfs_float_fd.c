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
 int SYSFS_MAX_INT ; 
 int /*<<< orphan*/  abort () ; 
 float atof (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

float read_sysfs_float_fd(int fd, const char *sys_pfx, const char *node)
{
	char buf[SYSFS_MAX_INT];

	if (read(fd, buf, sizeof(buf)) < 0) {

		fprintf(stderr, "unable to read from %s%s %s\n", sys_pfx, node,
			strerror(errno));
		close(fd);
		abort();
	}
	return atof(buf);
}