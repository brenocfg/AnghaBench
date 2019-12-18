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
struct file {scalar_t__ f_pos; int /*<<< orphan*/  f_version; int /*<<< orphan*/ * private_data; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static loff_t hmcdrv_dev_seek(struct file *fp, loff_t pos, int whence)
{
	switch (whence) {
	case SEEK_CUR: /* relative to current file position */
		pos += fp->f_pos; /* new position stored in 'pos' */
		break;

	case SEEK_SET: /* absolute (relative to beginning of file) */
		break; /* SEEK_SET */

		/* We use SEEK_END as a special indicator for a SEEK_SET
		 * (set absolute position), combined with a FTP command
		 * clear.
		 */
	case SEEK_END:
		if (fp->private_data) {
			kfree(fp->private_data);
			fp->private_data = NULL;
		}

		break; /* SEEK_END */

	default: /* SEEK_DATA, SEEK_HOLE: unsupported */
		return -EINVAL;
	}

	if (pos < 0)
		return -EINVAL;

	if (fp->f_pos != pos)
		++fp->f_version;

	fp->f_pos = pos;
	return pos;
}