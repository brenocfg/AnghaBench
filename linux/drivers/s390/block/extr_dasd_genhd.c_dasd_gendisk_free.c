#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dasd_block {TYPE_1__* gdp; } ;
struct TYPE_3__ {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_gendisk (TYPE_1__*) ; 
 int /*<<< orphan*/  put_disk (TYPE_1__*) ; 

void dasd_gendisk_free(struct dasd_block *block)
{
	if (block->gdp) {
		del_gendisk(block->gdp);
		block->gdp->private_data = NULL;
		put_disk(block->gdp);
		block->gdp = NULL;
	}
}