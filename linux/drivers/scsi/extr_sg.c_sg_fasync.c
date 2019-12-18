#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct file {scalar_t__ private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  async_qp; int /*<<< orphan*/ * parentdp; } ;
typedef  TYPE_1__ Sg_fd ;
typedef  int /*<<< orphan*/  Sg_device ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  SCSI_LOG_TIMEOUT (int,int /*<<< orphan*/ ) ; 
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
sg_fasync(int fd, struct file *filp, int mode)
{
	Sg_device *sdp;
	Sg_fd *sfp;

	if ((!(sfp = (Sg_fd *) filp->private_data)) || (!(sdp = sfp->parentdp)))
		return -ENXIO;
	SCSI_LOG_TIMEOUT(3, sg_printk(KERN_INFO, sdp,
				      "sg_fasync: mode=%d\n", mode));

	return fasync_helper(fd, filp, mode, &sfp->async_qp);
}