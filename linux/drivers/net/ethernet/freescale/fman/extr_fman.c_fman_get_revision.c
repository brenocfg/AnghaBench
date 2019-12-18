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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct fman_rev_info {int minor; scalar_t__ major; } ;
struct fman {TYPE_1__* fpm_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  fm_ip_rev_1; } ;

/* Variables and functions */
 int FPM_REV1_MAJOR_MASK ; 
 int FPM_REV1_MAJOR_SHIFT ; 
 int FPM_REV1_MINOR_MASK ; 
 int ioread32be (int /*<<< orphan*/ *) ; 

void fman_get_revision(struct fman *fman, struct fman_rev_info *rev_info)
{
	u32 tmp;

	tmp = ioread32be(&fman->fpm_regs->fm_ip_rev_1);
	rev_info->major = (u8)((tmp & FPM_REV1_MAJOR_MASK) >>
				FPM_REV1_MAJOR_SHIFT);
	rev_info->minor = tmp & FPM_REV1_MINOR_MASK;
}