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
struct st_modedef {unsigned long default_density; unsigned long default_blksize; } ;
struct scsi_tape {unsigned long density; unsigned long block_size; int /*<<< orphan*/  blksize_changed; int /*<<< orphan*/  density_changed; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 unsigned long MT_ST_DENSITY_SHIFT ; 
 int /*<<< orphan*/  SET_DENS_AND_BLK ; 
 scalar_t__ modes_defined ; 
 scalar_t__ st_int_ioctl (struct scsi_tape*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  st_printk (int /*<<< orphan*/ ,struct scsi_tape*,char*,unsigned long,unsigned long) ; 

__attribute__((used)) static int set_mode_densblk(struct scsi_tape * STp, struct st_modedef * STm)
{
	int set_it = 0;
	unsigned long arg;

	if (!STp->density_changed &&
	    STm->default_density >= 0 &&
	    STm->default_density != STp->density) {
		arg = STm->default_density;
		set_it = 1;
	} else
		arg = STp->density;
	arg <<= MT_ST_DENSITY_SHIFT;
	if (!STp->blksize_changed &&
	    STm->default_blksize >= 0 &&
	    STm->default_blksize != STp->block_size) {
		arg |= STm->default_blksize;
		set_it = 1;
	} else
		arg |= STp->block_size;
	if (set_it &&
	    st_int_ioctl(STp, SET_DENS_AND_BLK, arg)) {
		st_printk(KERN_WARNING, STp,
			  "Can't set default block size to %d bytes "
			  "and density %x.\n",
			  STm->default_blksize, STm->default_density);
		if (modes_defined)
			return (-EINVAL);
	}
	return 0;
}