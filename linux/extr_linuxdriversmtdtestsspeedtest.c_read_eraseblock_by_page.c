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
typedef  int loff_t ;
struct TYPE_3__ {int erasesize; } ;

/* Variables and functions */
 void* iobuf ; 
 TYPE_1__* mtd ; 
 int mtdtest_read (TYPE_1__*,int,scalar_t__,void*) ; 
 int pgcnt ; 
 scalar_t__ pgsize ; 

__attribute__((used)) static int read_eraseblock_by_page(int ebnum)
{
	int i, err = 0;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;
	void *buf = iobuf;

	for (i = 0; i < pgcnt; i++) {
		err = mtdtest_read(mtd, addr, pgsize, buf);
		if (err)
			break;
		addr += pgsize;
		buf += pgsize;
	}

	return err;
}