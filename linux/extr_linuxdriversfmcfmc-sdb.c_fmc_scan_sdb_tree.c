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
struct sdb_array {int dummy; } ;
struct fmc_device {struct sdb_array* sdb; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ IS_ERR (struct sdb_array*) ; 
 int PTR_ERR (struct sdb_array*) ; 
 struct sdb_array* __fmc_scan_sdb_tree (struct fmc_device*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int fmc_scan_sdb_tree(struct fmc_device *fmc, unsigned long address)
{
	struct sdb_array *ret;
	if (fmc->sdb)
		return -EBUSY;
	ret = __fmc_scan_sdb_tree(fmc, address, 0 /* regs */, 0);
	if (IS_ERR(ret))
		return PTR_ERR(ret);
	fmc->sdb = ret;
	return 0;
}