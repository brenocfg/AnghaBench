#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sg_fd {TYPE_2__* parentdp; } ;
struct file {int /*<<< orphan*/  f_mode; struct sg_fd* private_data; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ TYPE_SCANNER ; 
 int blk_verify_command (unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sg_allow_access(struct file *filp, unsigned char *cmd)
{
	struct sg_fd *sfp = filp->private_data;

	if (sfp->parentdp->device->type == TYPE_SCANNER)
		return 0;

	return blk_verify_command(cmd, filp->f_mode);
}