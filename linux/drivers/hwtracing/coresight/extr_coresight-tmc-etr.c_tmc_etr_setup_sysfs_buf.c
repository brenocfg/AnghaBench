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
struct tmc_drvdata {int /*<<< orphan*/  size; } ;
struct etr_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_node (int /*<<< orphan*/ ) ; 
 struct etr_buf* tmc_alloc_etr_buf (struct tmc_drvdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct etr_buf *
tmc_etr_setup_sysfs_buf(struct tmc_drvdata *drvdata)
{
	return tmc_alloc_etr_buf(drvdata, drvdata->size,
				 0, cpu_to_node(0), NULL);
}