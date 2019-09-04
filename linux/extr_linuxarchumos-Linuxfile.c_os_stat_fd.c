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
struct uml_stat {int dummy; } ;
struct stat64 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CATCH_EINTR (int) ; 
 int /*<<< orphan*/  copy_stat (struct uml_stat*,struct stat64*) ; 
 int errno ; 
 int fstat64 (int const,struct stat64*) ; 

int os_stat_fd(const int fd, struct uml_stat *ubuf)
{
	struct stat64 sbuf;
	int err;

	CATCH_EINTR(err = fstat64(fd, &sbuf));
	if (err < 0)
		return -errno;

	if (ubuf != NULL)
		copy_stat(ubuf, &sbuf);
	return err;
}