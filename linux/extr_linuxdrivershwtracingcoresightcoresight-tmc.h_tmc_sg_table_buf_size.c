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
struct TYPE_2__ {unsigned long nr_pages; } ;
struct tmc_sg_table {TYPE_1__ data_pages; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 

__attribute__((used)) static inline unsigned long
tmc_sg_table_buf_size(struct tmc_sg_table *sg_table)
{
	return sg_table->data_pages.nr_pages << PAGE_SHIFT;
}