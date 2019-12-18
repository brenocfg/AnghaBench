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
struct fsg_lun {int /*<<< orphan*/  unit_attention_data; scalar_t__ prevent_medium_removal; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  LDBG (struct fsg_lun*,char*) ; 
 int /*<<< orphan*/  SS_MEDIUM_NOT_PRESENT ; 
 int /*<<< orphan*/  SS_NOT_READY_TO_READY_TRANSITION ; 
 int /*<<< orphan*/  down_write (struct rw_semaphore*) ; 
 int /*<<< orphan*/  fsg_lun_close (struct fsg_lun*) ; 
 scalar_t__ fsg_lun_is_open (struct fsg_lun*) ; 
 int fsg_lun_open (struct fsg_lun*,char const*) ; 
 int /*<<< orphan*/  up_write (struct rw_semaphore*) ; 

ssize_t fsg_store_file(struct fsg_lun *curlun, struct rw_semaphore *filesem,
		       const char *buf, size_t count)
{
	int		rc = 0;

	if (curlun->prevent_medium_removal && fsg_lun_is_open(curlun)) {
		LDBG(curlun, "eject attempt prevented\n");
		return -EBUSY;				/* "Door is locked" */
	}

	/* Remove a trailing newline */
	if (count > 0 && buf[count-1] == '\n')
		((char *) buf)[count-1] = 0;		/* Ugh! */

	/* Load new medium */
	down_write(filesem);
	if (count > 0 && buf[0]) {
		/* fsg_lun_open() will close existing file if any. */
		rc = fsg_lun_open(curlun, buf);
		if (rc == 0)
			curlun->unit_attention_data =
					SS_NOT_READY_TO_READY_TRANSITION;
	} else if (fsg_lun_is_open(curlun)) {
		fsg_lun_close(curlun);
		curlun->unit_attention_data = SS_MEDIUM_NOT_PRESENT;
	}
	up_write(filesem);
	return (rc < 0 ? rc : count);
}