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
struct openflags {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 struct openflags OPENFLAGS () ; 
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/  W_OK ; 
 int access (char const*,int /*<<< orphan*/ ) ; 
 int errno ; 
 struct openflags of_read (struct openflags) ; 
 struct openflags of_write (struct openflags) ; 

int os_file_mode(const char *file, struct openflags *mode_out)
{
	int err;

	*mode_out = OPENFLAGS();

	err = access(file, W_OK);
	if (err && (errno != EACCES))
		return -errno;
	else if (!err)
		*mode_out = of_write(*mode_out);

	err = access(file, R_OK);
	if (err && (errno != EACCES))
		return -errno;
	else if (!err)
		*mode_out = of_read(*mode_out);

	return err;
}