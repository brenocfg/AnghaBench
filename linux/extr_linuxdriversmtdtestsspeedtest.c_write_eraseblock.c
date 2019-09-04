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
 int /*<<< orphan*/  iobuf ; 
 TYPE_1__* mtd ; 
 int mtdtest_write (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_eraseblock(int ebnum)
{
	loff_t addr = (loff_t)ebnum * mtd->erasesize;

	return mtdtest_write(mtd, addr, mtd->erasesize, iobuf);
}