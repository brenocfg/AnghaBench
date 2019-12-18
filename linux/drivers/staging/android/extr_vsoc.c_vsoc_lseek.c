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
struct file {int f_pos; } ;
typedef  int ssize_t ;
typedef  int loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int EOVERFLOW ; 
#define  SEEK_CUR 132 
#define  SEEK_DATA 131 
#define  SEEK_END 130 
#define  SEEK_HOLE 129 
#define  SEEK_SET 128 
 int vsoc_get_area (struct file*,int /*<<< orphan*/ *) ; 
 int vsoc_validate_filep (struct file*) ; 

__attribute__((used)) static loff_t vsoc_lseek(struct file *filp, loff_t offset, int origin)
{
	ssize_t area_len = 0;
	int retval = vsoc_validate_filep(filp);

	if (retval)
		return retval;
	area_len = vsoc_get_area(filp, NULL);
	switch (origin) {
	case SEEK_SET:
		break;

	case SEEK_CUR:
		if (offset > 0 && offset + filp->f_pos < 0)
			return -EOVERFLOW;
		offset += filp->f_pos;
		break;

	case SEEK_END:
		if (offset > 0 && offset + area_len < 0)
			return -EOVERFLOW;
		offset += area_len;
		break;

	case SEEK_DATA:
		if (offset >= area_len)
			return -EINVAL;
		if (offset < 0)
			offset = 0;
		break;

	case SEEK_HOLE:
		/* Next hole is always the end of the region, unless offset is
		 * beyond that
		 */
		if (offset < area_len)
			offset = area_len;
		break;

	default:
		return -EINVAL;
	}

	if (offset < 0 || offset > area_len)
		return -EINVAL;
	filp->f_pos = offset;

	return offset;
}