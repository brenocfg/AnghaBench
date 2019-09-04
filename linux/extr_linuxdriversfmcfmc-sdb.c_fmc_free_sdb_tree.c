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
struct fmc_device {int /*<<< orphan*/ * sdb; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fmc_sdb_free (int /*<<< orphan*/ *) ; 

int fmc_free_sdb_tree(struct fmc_device *fmc)
{
	__fmc_sdb_free(fmc->sdb);
	fmc->sdb = NULL;
	return 0;
}