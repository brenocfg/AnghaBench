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
struct fsg_lun {int /*<<< orphan*/  filp; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (char*) ; 
 scalar_t__ PAGE_SIZE ; 
 size_t PTR_ERR (char*) ; 
 int /*<<< orphan*/  down_read (struct rw_semaphore*) ; 
 char* file_path (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ fsg_lun_is_open (struct fsg_lun*) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  up_read (struct rw_semaphore*) ; 

ssize_t fsg_show_file(struct fsg_lun *curlun, struct rw_semaphore *filesem,
		      char *buf)
{
	char		*p;
	ssize_t		rc;

	down_read(filesem);
	if (fsg_lun_is_open(curlun)) {	/* Get the complete pathname */
		p = file_path(curlun->filp, buf, PAGE_SIZE - 1);
		if (IS_ERR(p))
			rc = PTR_ERR(p);
		else {
			rc = strlen(p);
			memmove(buf, p, rc);
			buf[rc] = '\n';		/* Add a newline */
			buf[++rc] = 0;
		}
	} else {				/* No file, return 0 bytes */
		*buf = 0;
		rc = 0;
	}
	up_read(filesem);
	return rc;
}