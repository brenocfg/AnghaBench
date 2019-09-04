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
struct fmc_device {TYPE_1__* op; } ;
struct TYPE_2__ {int (* write_ee ) (struct fmc_device*,int,void const*,int) ;} ;

/* Variables and functions */
 int EPERM ; 
 int stub1 (struct fmc_device*,int,void const*,int) ; 

int fmc_write_ee(struct fmc_device *fmc, int pos, const void *d, int l)
{
	if (fmc->op->write_ee)
		return fmc->op->write_ee(fmc, pos, d, l);
	return -EPERM;
}