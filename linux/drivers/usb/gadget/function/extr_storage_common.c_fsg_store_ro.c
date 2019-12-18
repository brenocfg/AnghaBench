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
struct rw_semaphore {int dummy; } ;
struct fsg_lun {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t _fsg_store_ro (struct fsg_lun*,int) ; 
 int /*<<< orphan*/  down_read (struct rw_semaphore*) ; 
 size_t strtobool (char const*,int*) ; 
 int /*<<< orphan*/  up_read (struct rw_semaphore*) ; 

ssize_t fsg_store_ro(struct fsg_lun *curlun, struct rw_semaphore *filesem,
		     const char *buf, size_t count)
{
	ssize_t		rc;
	bool		ro;

	rc = strtobool(buf, &ro);
	if (rc)
		return rc;

	/*
	 * Allow the write-enable status to change only while the
	 * backing file is closed.
	 */
	down_read(filesem);
	rc = _fsg_store_ro(curlun, ro);
	if (!rc)
		rc = count;
	up_read(filesem);

	return rc;
}