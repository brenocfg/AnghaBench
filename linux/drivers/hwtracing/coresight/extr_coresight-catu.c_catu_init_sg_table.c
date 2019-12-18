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
struct tmc_sg_table {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int CATU_PAGES_PER_SYSPAGE ; 
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct tmc_sg_table*) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  SZ_1M ; 
 int /*<<< orphan*/  catu_dump_table (struct tmc_sg_table*) ; 
 int /*<<< orphan*/  catu_populate_table (struct tmc_sg_table*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct tmc_sg_table*,unsigned long,int) ; 
 struct tmc_sg_table* tmc_alloc_sg_table (struct device*,int,int,int,void**) ; 

__attribute__((used)) static struct tmc_sg_table *
catu_init_sg_table(struct device *catu_dev, int node,
		   ssize_t size, void **pages)
{
	int nr_tpages;
	struct tmc_sg_table *catu_table;

	/*
	 * Each table can address upto 1MB and we can have
	 * CATU_PAGES_PER_SYSPAGE tables in a system page.
	 */
	nr_tpages = DIV_ROUND_UP(size, SZ_1M) / CATU_PAGES_PER_SYSPAGE;
	catu_table = tmc_alloc_sg_table(catu_dev, node, nr_tpages,
					size >> PAGE_SHIFT, pages);
	if (IS_ERR(catu_table))
		return catu_table;

	catu_populate_table(catu_table);
	dev_dbg(catu_dev,
		"Setup table %p, size %ldKB, %d table pages\n",
		catu_table, (unsigned long)size >> 10,  nr_tpages);
	catu_dump_table(catu_table);
	return catu_table;
}